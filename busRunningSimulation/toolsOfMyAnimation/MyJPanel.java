package busRunningSimulation.toolsOfMyAnimation;

import javax.swing.*;
import java.awt.*;

public class MyJPanel extends JPanel {
    private BusExample[] busExamples;

    public MyJPanel(BusExample[] busExam) {
        this.busExamples = busExam;
    }//接受对象数组

    @Override
    public void paint(Graphics g) {
        super.paint(g);
        for (BusExample busExample : busExamples) {//分别画出各个对象
            g.drawImage(busExample.getImage(),busExample.getX(),busExample.getY(),busExample.getWidth(),busExample.getHeight(),null);
        }
    }
}
