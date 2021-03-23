package busRunningSimulation.bus;

import busRunningSimulation.passengers.Passengers;

import java.util.LinkedHashMap;

public abstract class Bus {
      public String name = null;//客车名
      public int passengers = 0;//载客人数
      public double distance = 0;//距离出发点的距离
      public String myLocation = null;//当前位置
      public int startTime = 0;//发车时的时间
      public double speed = 0;//客车速度
      public int stopTimes = 0;//客车停车次数
      public int totalLoad = 0;//客车的最大载重
      public String startPlace = null;//初始位置
      public boolean isStop = false;//是否处于停车状态
      public boolean isStart = false;//是否出发
      public boolean finalStop = false;//是否不再出发
      public int waitTimes = 0;//停车时长
      public int nextTime = 0;//相邻两车之间的发车时间
      public int endTime = 0;//最后一班发车时间

       abstract void getNewPassengers(Passengers passengers, Bus[] bus, int time);//到达终点站，开始增加新的乘客

       abstract String returnLocation(LinkedHashMap<String,Double> busStop, int time);//返回客车当前位置

       abstract boolean getOffBus();//判断乘客是否下车并更新乘客数量

       abstract void initializePassengers(Passengers passengers);//用于客车刚发车时的乘客数量初始化
}
