package busRunningSimulation.bus;

import busRunningSimulation.passengers.Passengers;
import java.util.LinkedHashMap;
import java.util.Map;
import java.util.Set;

public class Iveco extends Bus {
    public String name = "IVECO";
    public int passengers = 0;
    public double distance = 0;
    public String myLocation = null;
    public int startTime = 0;
    public double speed = 1.4;
    public int totalLoad = 21;
    public int stopTimes = 0;
    public boolean finalStop = false;
    public String startPlace = null;//初始位置
    public boolean isStop = false;
    public boolean isStart = false;
    public int waitTimes = 0;
    public int nextTime = 20;
    public int endTime = 600;

    public void getNewPassengers(Passengers passengers, Bus[] bus, int time){
        //            乘客上车并更新站台乘客数量
        int numbers = this.passengers;//获取当前客车乘客数量
        int numOfPrevious = this.passengers;//记录目前乘客数量
        if(startPlace == "XN"){//出发地为西安
            numbers = passengers.getNumberOfPassengersinBJ();
            if (numbers>=totalLoad){//如果车站乘客大于客车最大载客数量
                this.passengers = totalLoad;
                passengers.setNumberOfPassengersinBJ(numbers - totalLoad);//更新车站待乘人数
            }else{
                this.passengers = numbers;
                passengers.setNumberOfPassengersinBJ(0);
            }
            startPlace = "BJ";//初始车站更换,相应属性参数更新
            distance = 174;
            stopTimes = 0;
        }else if(startPlace == "BJ"){//出发地为宝鸡
            numbers = passengers.getNumberOfPassengersinXN();
            if (numbers>=totalLoad){//如果车站乘客大于客车最大载客数量
                this.passengers = totalLoad;
                passengers.setNumberOfPassengersinXN(numbers - totalLoad);//更新车站待乘人数
            }else{
                this.passengers = numbers;
                passengers.setNumberOfPassengersinXN(0);
            }
            startPlace = "XN";//初始车站更换,相应属性参数更新
            distance = 0;
            stopTimes = 0;
        }
        if(waitTimes>0){//如果客车处于停车状态则停车次数加1
            stopTimes = 1;
        }

        int max = 0;
        for (Bus Iveco : bus) {//找出最近一班车的发车时间
            if(startPlace == Iveco.startPlace){
                if (max<Iveco.startTime){
                    max = Iveco.startTime;
                }
            }
        }
        if(time-max>=nextTime){//如果上一班车已经走了超过相邻发车时间，则这一班车可以直接发出,否则需等待到下一次发车时间
            startTime = time;
            isStart = true;//可发车
        }else{
            startTime = max + nextTime;
            isStart = false;//不能发车
        }
        if(endTime>=startTime){//如果客车的发车时间还未过最后一班车的发车时间
            System.out.println("新上车乘客数量："+(this.passengers-numOfPrevious));
        }
    }

    public String returnLocation(LinkedHashMap<String,Double> busStop, int time){
        Set<Map.Entry<String, Double>> set = busStop.entrySet();
        if(waitTimes>0){//处于停车状态位置不变
            return myLocation;
        }
        if(finalStop == true){//处于不再发车状态位置不变
            return myLocation;
        }
        //查看出发点，检查客车是否出发，根据时间计算客车所走路程
        if(startPlace == "XN"&&isStart){
            distance = (time-startTime-stopTimes*2)*speed;
            if(distance>174){//两次循环之间可能到达终点站
                distance = 174;
            }
            for(Map.Entry<String,Double> entry : set){//循环遍历车站
                if(distance==entry.getValue()){//如果客车行驶距离恰好等于所获得车站所处距离
                    myLocation = entry.getKey();
                    break;
                }else if((distance<entry.getValue())&&distance>0){//如果客车行驶距离小于此当前遍历的车站，并且行驶距离大于0
                    int approDistance = (int)(entry.getValue()-distance);//将double类型距离转换成近似大小的整数
                    myLocation = "距离"+entry.getKey()+approDistance+"公里";
                    break;
                }else if((distance>entry.getValue())&&distance>0
                        &&((distance-speed)<entry.getValue())&&((distance-speed)>0)){//如果在两次循环间隔之间到了车站，则需判定是否停车
                    if(getOffBus()){//如果停车，更新客车相应的行驶距离，位置，停车时间
                        distance = entry.getValue();
                        myLocation = entry.getKey();
                        waitTimes = 2;
                    }else{
                        int approDistance = (int)(distance-entry.getValue());//将double类型距离转换成近似大小的整数
                        myLocation = "距离"+entry.getKey()+approDistance+"公里";
                    }
                    break;
                }
            }
        }           /*由于客车只是在宝鸡和西安之间的行驶方向相反，故相应的参数改变与上面类似*/
        else if(startPlace == "BJ"&&isStart){
            distance = busStop.get("BJ")-(time-startTime-stopTimes*2)*speed;
            if(distance<0){
                distance = 0;
            }
            for(Map.Entry<String,Double> entry : set){
                if(distance==entry.getValue()){
                    myLocation = entry.getKey();
                    break;
                }else if ((distance<entry.getValue())&&distance>0){
                    if(((distance+speed)>entry.getValue())&&((time-startTime)!=1)){//判断是否在两次循环间到达车站
                        if(getOffBus()){//判断是否停车
                            distance = entry.getValue();
                            myLocation = entry.getKey();
                            waitTimes = 2;
                        }else{
                            int approDistance = (int)(entry.getValue()-distance);//将double类型距离转换成近似大小的整数
                            myLocation = "距离"+entry.getKey()+approDistance+"公里";
                        }

                    }else{
                        int approDistance = (int)(entry.getValue()-distance);//将double类型距离转换成近似大小的整数
                        myLocation = "距离"+entry.getKey()+approDistance+"公里";
                    }
                    break;
                }
            }
        }
        return myLocation;  //获取当前位置
    }

    public boolean getOffBus(){
        if(endTime >= startTime){//如果客车仍出发
            if((myLocation == "XN"||myLocation == "BJ")&&passengers>0) {//在终点站全部乘客下车
                System.out.println("有乘客下车，下车人数为：" + passengers);
                passengers = 0;
                stopTimes++;
                isStop = true;
            }
            double ifGetOff = Math.random();//获取乘客下车的概率
            long countOfPassengers = Math.round(Math.random()*passengers);//下车人数
            if(ifGetOff >= 0.5&&countOfPassengers>0){//必须满足下车人数大于0
                    System.out.println("有乘客下车，下车人数为："+countOfPassengers);
                    passengers-=countOfPassengers;//更新乘客数
                    System.out.println("剩下的乘客数量："+passengers);
                    stopTimes++;//停车次数增加
                isStop = true;//处于停车状态
            }else{
                isStop = false;//处于行驶状态
            }
        }else{
            System.out.println("本次客车运行已结束，剩余下车的乘客数量： "+passengers);
            this.passengers = 0;//清空客车内的乘客数量
            isStop = true;//处于停车状态
        }
        return isStop;//处于行驶状态
    }
        //具体效果与getNewPassengers方法类似，用于初始化客车的乘客参数
    public void initializePassengers(Passengers passengers){
        //实现过程逻辑与getNewPassengers大致相同，不再赘述
        int numbers = 0;
        if(startPlace == "XN"){
            numbers = passengers.getNumberOfPassengersinXN();
            if (numbers>=totalLoad){
                this.passengers = totalLoad;
                passengers.setNumberOfPassengersinXN(numbers - totalLoad);
            }else{
                this.passengers = numbers;
                passengers.setNumberOfPassengersinXN(0);
            }
        }else{
            numbers = passengers.getNumberOfPassengersinBJ();
            if (numbers>=totalLoad){
                this.passengers = totalLoad;
                passengers.setNumberOfPassengersinBJ(numbers - totalLoad);
            }else{
                this.passengers = numbers;
                passengers.setNumberOfPassengersinBJ(0);
            }
        }
        System.out.println("新上车人数为："+this.passengers);
    }
}
