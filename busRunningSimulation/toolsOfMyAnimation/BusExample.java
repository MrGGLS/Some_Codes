package busRunningSimulation.toolsOfMyAnimation;

import javax.swing.*;
import java.awt.*;

public class BusExample extends JPanel {
  private int x,y,width,height;//图像布局参数
  private String imageName;//图像名称
  private Image image;//自定义图片

    @Override
    public int getX() {
        return x;
    }

    public Image getImage() {
        return image;
    }

    public void setX(int x) {
        this.x = x;
    }

    @Override
    public int getY() {
        return y;
    }

    public void setY(int y) {
        this.y = y;
    }

    @Override
    public int getWidth() {
        return width;
    }

    public void setWidth(int width) {
        this.width = width;
    }

    @Override
    public int getHeight() {
        return height;
    }

    public String getImageName() {
        return imageName;
    }

    public void setImageName(String imageName) {
        this.imageName = imageName;
    }

    public void setHeight(int height) {
        this.height = height;
    }

    public BusExample(String imageName,int x,int y,int width,int height) {//使用Getter和Setter获得所需参数
        this.imageName = imageName;
        this.image = new ImageIcon("BusRunningSimulation/resourse/"+this.imageName).getImage();//通过所获得的图像名获取图片
        this.x = x;
        this.y = y;
        this.width = width;
        this.height = height;
    }
}
