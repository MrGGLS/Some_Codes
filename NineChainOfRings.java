import java.util.Scanner;

public class NineChainOfRings {

    public static void main(String[] args) {
        Scanner input = new Scanner(System.in);
        System.out.print("请输入环的个数：");
        int numberOfRings = input.nextInt();
        ringDown(numberOfRings);
        System.out.println("总共所需步数："+count);

    }

        static int count = 0;
    public static void ringDown(int n){

        if(n > 2){
            //想要下第n环必须先下前n-2环
            ringDown(n - 2);
        }

        if(n == 2){
            //简化操作，直接下前一二环
            System.out.println("前一二环一起下");
        }else{
            //第一步已下好前n-2环，故可下第n环
            System.out.println("下第"+n+"环");
        }
        count++;

        if(n > 2){
            //想要下第n-1环，先上前n-2环
            ringUp(n - 2);
        }

        if(n > 2){
            //问题从下载前n环变为下载前n-1环
            //继续递归
            ringDown(n - 1);
        }

    }
        /*上环实为下环的逆过程，
        * 在此不再赘述，请读者
        * 自行查看
        * */
    public static void ringUp(int n){

            if(n > 2){
                ringUp(n - 1);
            }

            if(n == 2){
                System.out.println("前一二环一起上");
            }else{
                System.out.println("上第"+n+"环");
            }
        count++;

        if(n >2){
                ringDown(n - 2);
            }

            if(n > 2){
                ringUp(n - 2);
            }

    }

}
