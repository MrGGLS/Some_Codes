package busRunningSimulation.busLauncher;

import busRunningSimulation.bus.Iveco;
import busRunningSimulation.bus.Volvo;
import busRunningSimulation.passengers.Passengers;
import busRunningSimulation.toolsOfMyAnimation.BusExample;
import busRunningSimulation.toolsOfMyAnimation.MyJPanel;
import javax.swing.*;
import java.util.LinkedHashMap;
import java.util.Scanner;
import java.util.Set;

import static java.lang.Thread.sleep;

public class Main extends JFrame {
        //动画布局
    public Main(){
        this.setTitle("客车模拟运行演示动画");//设置标题
        this.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);//设置关闭方式
        this.setSize(800,300);//设置窗口大小
        LinkedHashMap<String,Double> busStop = new LinkedHashMap<>();//储存站台及其距西安站距离
        busStop.put("XN",0.0);
        busStop.put("XY",22.0);
        busStop.put("XP",46.0);
        busStop.put("WG",67.0);
        busStop.put("CP",129.0);
        busStop.put("GZ",150.0);
        busStop.put("BJ",174.0);
        int time = 0;//这里的时间代表7:30
        System.out.println("欢迎来到本次的客车模拟实验，我是你们的车长广哥拉斯");
        try {
            sleep(1000);
        } catch (InterruptedException e) {
            e.printStackTrace();
        }
        System.out.println("客车即将发行，请乘客有序上车");
        try {
            sleep(1000);
        } catch (InterruptedException e) {
            e.printStackTrace();
        }
        int countVolvo = 0;//统计停止发车的Volvo数量
        int countIveco = 0;//统计停止发车的Iveco数量

        Scanner scanner = new Scanner(System.in);//获取用户输入信息以改变客车的初始数量

        System.out.print("请输入在西安站的依维柯的数量：");
        int inumOfXN = scanner.nextInt();
        System.out.println("");
        System.out.print("请输入在宝鸡站的依维柯数量：");
        int inumOfBJ = scanner.nextInt();
        System.out.println("");
        Iveco[] iveco = new Iveco[inumOfBJ+inumOfXN];//创建依维柯车队

        System.out.print("请输入在西安站的沃尔沃数量：");
        int vnumOfXN = scanner.nextInt();
        System.out.println("");
        System.out.print("请输入在宝鸡站的沃尔沃数量：");
        int vnumOfBJ = scanner.nextInt();
        System.out.println("");
        Volvo[] volvo = new Volvo[vnumOfBJ+vnumOfXN];//创建沃尔沃车队

        BusExample[] busExamples = new BusExample[volvo.length+iveco.length+7];//创建客车动画实例
        MyJPanel myJpanel = new MyJPanel(busExamples);//进行绘画

        initializeIveco(busExamples,inumOfXN,inumOfBJ,iveco,30);//初始化依维柯车队
        initializeVolvo(iveco.length,busExamples,vnumOfXN,vnumOfBJ,volvo,60);//初始化沃尔沃车队
        //添加各个站点的图片
        busExamples[volvo.length+iveco.length] = new BusExample("XN.png",30,160,60,30);
        busExamples[volvo.length+iveco.length+1] = new BusExample("XY.png",30+22*3,160,60,30);
        busExamples[volvo.length+iveco.length+2] = new BusExample("XP.png",30+46*3,160,60,30);
        busExamples[volvo.length+iveco.length+3] = new BusExample("WG.png",30+67*3,160,60,30);
        busExamples[volvo.length+iveco.length+4] = new BusExample("CP.png",30+129*3,160,60,30);
        busExamples[volvo.length+iveco.length+5] = new BusExample("GZ.png",30+150*3,160,60,30);
        busExamples[volvo.length+iveco.length+6] = new BusExample("BJ.png",30+174*3,160,60,30);
        this.add(myJpanel);//添加myJpanel
        this.setVisible(true);//设置可见，默认为false

        Passengers passengers = new Passengers();//创建Passengers类的实例以储存和改变passengers数量
//        Set<String> strings = busStop.keySet();
//        System.out.println(strings);
        while(countIveco<iveco.length||countVolvo<volvo.length){//在所有车都处于不再发车状态时退出循环
            countIveco = 0;//用于统计不再发车的依维柯数量
            countVolvo = 0;//用于统计不再发车的沃尔沃数量
            formatTime(time);//让时间格式化输出
            if(time < 600){//在下午六点前每次循环都增加宝鸡和西安站的待乘人数
                passengers.addNewPassengers(time);
//                System.out.println(passengers.getNumberOfPassengersinXN());
            }

            runIveco(busExamples,iveco,busStop,time,passengers);//运行Iveco车队
            System.out.println("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
            runVolvo(iveco.length,busExamples,volvo,busStop,time,passengers);//运行Volvo车队
            System.out.println("***********************************");
            myJpanel.repaint();//重画界面
            if(time >= 600){//六点后不再有新的依维柯出发
                for (Iveco eachIveco : iveco) {
                    if(eachIveco.startTime>600){//Iveco大于六点半不再出发
                        eachIveco.finalStop = true;
                        countIveco++;
                    }
                }
            }

            if(time >= 570){//五点半后不再有新的沃尔沃出发
                for (Volvo eachVolvo : volvo) {
                    if(eachVolvo.startTime>570){//Volvo大于六点不再出发
                        eachVolvo.finalStop = true;
                        countVolvo++;
                    }
                }
            }

            time++;
            try {
                sleep(50);//设置每分钟的间隔
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
        }
        System.out.println("");
        System.out.println("*************************************");
        System.out.println("本次客车模拟运行实验已结束，剩下的乘客请明天再来");
    }
        //动画演示
    public static void main(String[] args) {
        new Main();
    }

        //格式化时间
    public static void formatTime(int time){
        time = time + 450;
        int hour = time/60;
        int minutes = time%60;
        if(minutes>9){
            System.out.println("北京时间: "+hour+":"+minutes);
        }else{
            System.out.println("北京时间: "+hour+":0"+minutes);
        }

    }

            /*初始化巴士的数量以及发车时间*/
    public static void initializeIveco(BusExample[] examples,int numOfXN, int numOfBJ, Iveco[] bus, int startTime){
            for (int i = 0; i <numOfXN ; i++) {
                bus[i] = new Iveco();
                bus[i].startPlace = "XN";
                bus[i].myLocation = "XN";
                bus[i].startTime = 20*i+startTime;
                bus[i].name = bus[i].name+i+"号";
                examples[i] = new BusExample("Iveco.png",30,50,50,50);//初始化客车的图像参数
            }
            for(int i = numOfXN;i<(numOfBJ+numOfXN);i++){
                bus[i] = new Iveco();
                bus[i].startPlace = "BJ";
                bus[i].myLocation = "BJ";
                bus[i].startTime = 20*(i-numOfXN)+startTime;
                bus[i].name = bus[i].name+i+"号";
                examples[i] = new BusExample("Iveco.png",30+174*2,50,50,50);//初始化客车的图像参数
            }
    }

    public static void initializeVolvo(int startOfVolvo,BusExample[] examples,int numOfXN, int numOfBJ, Volvo[] bus, int startTime){
        for (int i = 0; i <numOfXN ; i++) {
            bus[i] = new Volvo();
            bus[i].startPlace = "XN";
            bus[i].myLocation = "XN";
            bus[i].startTime = 60*i+startTime;
            bus[i].name = bus[i].name+i+"号";
            examples[i+startOfVolvo] = new BusExample("Volvo.png",30,100,50,50);//初始化客车的图像参数
        }
        for(int i = numOfXN;i<(numOfBJ+numOfXN);i++){
            bus[i] = new Volvo();
            bus[i].startPlace = "BJ";
            bus[i].myLocation = "BJ";
            bus[i].startTime = 60*(i-numOfXN)+startTime;
            bus[i].name = bus[i].name+i+"号";
            examples[i+startOfVolvo] = new BusExample("Volvo.png",30+174*2,100,50,50);//初始化客车的图像参数
        }
    }

            //使用runBus()模拟巴士运行
    public static void runIveco(BusExample[] examples,Iveco[] bus, LinkedHashMap<String,Double> busStop,
                                int time, Passengers passengers){
        int i = 0;
        for (Iveco eachBUS : bus) {
        if(eachBUS.finalStop == false){
            String location = eachBUS.returnLocation(busStop, time);
            examples[i].setX(30+(int)(eachBUS.distance*3));//每次重画时改变对象距离
            System.out.println(eachBUS.name+": "+"出发地："+eachBUS.startPlace+"站  目前所在位置： "+eachBUS.myLocation+" 当前乘客数量："+eachBUS.passengers);
//                if(eachBUS.startTime>time){//判断是否客车处于起点站台
//                    System.out.println("I'm the starting platform.");
//                }

            if(eachBUS.startTime == time){//到达发车时间，客车发动
                eachBUS.initializePassengers(passengers);
                System.out.println("最大载客量："+eachBUS.totalLoad+" 当前乘客数量："+eachBUS.passengers);
                eachBUS.isStart = true;
            }

            if (eachBUS.waitTimes>0){ //如果客车处于停车时间，则停车时间减少1分钟
                eachBUS.waitTimes--;
                System.out.println("仍处于停车状态");
            }
            else{
                if((location == "XN"||location == "BJ")&&eachBUS.isStart&&((eachBUS.startTime+1) < time)){//判断是否到终点站
                    boolean isStop = eachBUS.getOffBus();//判断乘客下车
                    if(isStop){
                        eachBUS.waitTimes = 2;//客车停车时间为2分钟
                    }
                    eachBUS.getNewPassengers(passengers, bus, time);//增加新的乘客并改变客车相应参数
                }else{
                    Set<String> set = busStop.keySet();
                    for (String s : set) {
                        //判断客车是否到站以及是否是刚到站状态
                        if(eachBUS.myLocation == s && eachBUS.waitTimes == 0&&eachBUS.isStart&&((eachBUS.startTime+1) < time)){
                            boolean isStop = eachBUS.getOffBus();//判断乘客下车
                            if(isStop){
                                eachBUS.waitTimes = 2;//客车停车时间为2分钟
                            }
                            break;
                        }
                    }
                }
            }
        }
        i++;
        }
    }

    public static void runVolvo(int startOfVolvo,BusExample[] examples,Volvo[] bus, LinkedHashMap<String,Double> busStop,
                                int time, Passengers passengers) {
        {
            int i = startOfVolvo;
            for (Volvo eachBUS : bus) {
                if(eachBUS.finalStop == false){
                    String location = eachBUS.returnLocation(busStop, time);
                    examples[i].setX(30+(int)(eachBUS.distance*3));//每次重画时改变对象距离
                    System.out.println(eachBUS.name+": "+"出发地："+eachBUS.startPlace+"站  目前所在位置： "+eachBUS.myLocation+" 当前乘客数量："+eachBUS.passengers);
//                if(eachBUS.startTime>time){//判断是否客车处于起点站台
//                    System.out.println("I'm the starting platform.");
//                }

                    if(eachBUS.startTime == time){//到达发车时间，客车发动
                        eachBUS.initializePassengers(passengers);
                        System.out.println("最大载客量："+eachBUS.totalLoad+" 当前乘客数量："+eachBUS.passengers);
                        eachBUS.isStart = true;
                    }

                    if (eachBUS.waitTimes>0){ //如果客车处于停车时间，则停车时间减少1分钟
                        eachBUS.waitTimes--;
                        System.out.println("仍处于停车状态");
                    }
                    else{
                        if((location == "XN"||location == "BJ")&&eachBUS.isStart&&((eachBUS.startTime+1) < time)){//判断是否到终点站
                            boolean isStop = eachBUS.getOffBus();//判断乘客下车
                            if(isStop){
                                eachBUS.waitTimes = 2;//客车停车时间为2分钟
                            }
                            eachBUS.getNewPassengers(passengers, bus, time);//增加新的乘客并改变客车相应参数
                        }else{
                            Set<String> set = busStop.keySet();
                            for (String s : set) {
                                //判断客车是否到站以及是否是刚到站状态
                                if(eachBUS.myLocation == s && eachBUS.waitTimes == 0&&eachBUS.isStart&&((eachBUS.startTime+1) < time)){
                                    boolean isStop = eachBUS.getOffBus();//判断乘客下车
                                    if(isStop){
                                        eachBUS.waitTimes = 2;//客车停车时间为2分钟
                                    }
                                    break;
                                }
                            }
                        }
                    }
                }
            i++;
            }
        }
    }
}
