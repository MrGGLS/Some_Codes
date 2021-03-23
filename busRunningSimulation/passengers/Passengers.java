package busRunningSimulation.passengers;

public class Passengers {
    public int getNumberOfPassengersinXN() {
        return numberOfPassengersinXN;
    }

    public void setNumberOfPassengersinXN(int numberOfPassengersinXN) {
        this.numberOfPassengersinXN = numberOfPassengersinXN;
    }

    public int getNumberOfPassengersinBJ() {
        return numberOfPassengersinBJ;
    }

    public void setNumberOfPassengersinBJ(int numberOfPassengersinBJ) {
        this.numberOfPassengersinBJ = numberOfPassengersinBJ;
    }
        //运用随机数获得两站乘客的初始值，可以由用户自行更改
     private int numberOfPassengersinXN = (int)Math.random()*600;
     private int numberOfPassengersinBJ = (int)Math.random()*600;

     public void addNewPassengers(int time){
         if(time>=0&&time<600){
             numberOfPassengersinXN+=Math.random()*100;
             numberOfPassengersinBJ+=Math.random()*100;
         }
    }  //每分钟分别在西安和宝鸡随机增加0~2人
}
