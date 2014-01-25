/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package nimbus;

import java.awt.AWTEvent;
import java.awt.Component;
import java.awt.GridLayout;
import java.awt.Point;
import java.awt.Toolkit;
import java.awt.event.AWTEventListener;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.MouseEvent;
import java.util.ArrayList;
import javax.swing.JFrame;
import javax.swing.SwingUtilities;
import javax.swing.Timer;

/**
 *
 * @author Wrench
 */
public class Nimbus {

    /**
     * @param args the command line arguments
     */
    public static void main(String[] args) {
        SwingUtilities.invokeLater(new Runnable() {
            @Override
            public void run() {
                createAndShowGUI();
            }
        });
    }

    private static void createAndShowGUI() {
        final JFrame f = new JFrame("Swing Paint Demo");
        f.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        f.setSize(500, 500);
        f.setLayout(new GridLayout(10, 10));
        f.setVisible(true);
        final ArrayList<Wind> wind = new ArrayList<>();

        Toolkit.getDefaultToolkit().addAWTEventListener(new AWTEventListener() {
            @Override
            public void eventDispatched(AWTEvent event) {
                if (event instanceof MouseEvent) {
                    MouseEvent evt = (MouseEvent) event;

                    if (evt.getID() == MouseEvent.MOUSE_PRESSED) {
                        if (evt.getButton() == MouseEvent.BUTTON1){
                            wind.add(new Wind(10));
                        }
                        if (evt.getButton() == MouseEvent.BUTTON3){
                            wind.add(new Wind(-1));
                        }
                        
                    }//end if

                    if (evt.getID() == MouseEvent.MOUSE_RELEASED) {
                        if (wind.get(wind.size() - 1).path.size() > 1) {
                            wind.get(wind.size() - 1).complete = true;
                        } else {
                            wind.remove(wind.size() - 1);
                        }

                    }//end if

                    if (evt.getID() == MouseEvent.MOUSE_DRAGGED) {
                        Point point = evt.getPoint();

                        Component component =
                                SwingUtilities.getDeepestComponentAt(
                                evt.getComponent(),
                                point.x,
                                point.y);

                        if (component != null && component instanceof NodePanel) {
                            NodePanel comp = (NodePanel) component;
                            if (wind.get(wind.size() - 1).path.isEmpty()) {
                                wind.get(wind.size() - 1).add(comp);
                            }
                            if (!wind.get(wind.size() - 1).peek().equals(comp)) {
                                wind.get(wind.size() - 1).add(comp);
                            }
                        }
                    }
                }
            }
        }, AWTEvent.MOUSE_MOTION_EVENT_MASK | AWTEvent.MOUSE_EVENT_MASK);

        NodePanel[][] nodes;
        nodes = new NodePanel[10][10];
        nodes[0][0] = new NodePanel(80, 10, 0, 50, false, NodePanel.OCEAN);
        nodes[0][1] = new NodePanel(80, 10, 0, 50, false, NodePanel.OCEAN);
        nodes[0][2] = new NodePanel(80, 10, 0, 50, false, NodePanel.OCEAN);
        nodes[0][3] = new NodePanel(80, 10, 0, 50, false, NodePanel.OCEAN);
        nodes[0][4] = new NodePanel(80, 10, 0, 50, false, NodePanel.OCEAN);
        nodes[0][5] = new NodePanel(80, 10, 0, 50, false, NodePanel.OCEAN);
        nodes[0][6] = new NodePanel(80, 10, 0, 50, false, NodePanel.OCEAN);
        nodes[0][7] = new NodePanel(80, 10, 0, 50, false, NodePanel.OCEAN);
        nodes[0][8] = new NodePanel(80, 10, 0, 50, false, NodePanel.OCEAN);
        nodes[0][9] = new NodePanel(80, 10, 0, 50, false, NodePanel.OCEAN);
        nodes[1][0] = new NodePanel(80, 10, 0, 50, false, NodePanel.OCEAN);
        nodes[1][1] = new NodePanel(80, 10, 0, 50, false, NodePanel.OCEAN);
        nodes[1][2] = new NodePanel(10, 10, 0, 50, false, NodePanel.DESERT);
        nodes[1][3] = new NodePanel(10, 10, 0, 50, false, NodePanel.DESERT);
        nodes[1][4] = new NodePanel(10, 10, 0, 50, false, NodePanel.DESERT);
        nodes[1][5] = new NodePanel(10, 10, 0, 50, false, NodePanel.DESERT);
        nodes[1][6] = new NodePanel(10, 10, 0, 50, false, NodePanel.DESERT);
        nodes[1][7] = new NodePanel(10, 10, 0, 50, false, NodePanel.DESERT);
        nodes[1][8] = new NodePanel(10, 10, 0, 50, false, NodePanel.DESERT);
        nodes[1][9] = new NodePanel(80, 10, 0, 50, false, NodePanel.OCEAN);
        nodes[2][0] = new NodePanel(80, 10, 0, 50, false, NodePanel.OCEAN);
        nodes[2][1] = new NodePanel(80, 10, 0, 50, false, NodePanel.OCEAN);
        nodes[2][2] = new NodePanel(10, 10, 0, 50, false, NodePanel.DESERT);
        nodes[2][3] = new NodePanel(10, 10, 0, 50, false, NodePanel.MOUNTAIN);
        nodes[2][4] = new NodePanel(10, 10, 0, 50, false, NodePanel.DESERT);
        nodes[2][5] = new NodePanel(10, 10, 0, 50, false, NodePanel.DESERT);
        nodes[2][6] = new NodePanel(10, 10, 0, 50, false, NodePanel.DESERT);
        nodes[2][7] = new NodePanel(10, 10, 0, 50, false, NodePanel.DESERT);
        nodes[2][8] = new NodePanel(10, 10, 0, 50, false, NodePanel.DESERT);
        nodes[2][9] = new NodePanel(80, 10, 0, 50, false, NodePanel.OCEAN);
        nodes[3][0] = new NodePanel(80, 10, 0, 50, false, NodePanel.OCEAN);
        nodes[3][1] = new NodePanel(80, 10, 0, 50, false, NodePanel.OCEAN);
        nodes[3][2] = new NodePanel(10, 10, 0, 50, false, NodePanel.DESERT);
        nodes[3][3] = new NodePanel(10, 10, 0, 50, false, NodePanel.MOUNTAIN);
        nodes[3][4] = new NodePanel(10, 10, 0, 50, false, NodePanel.DESERT);
        nodes[3][5] = new NodePanel(10, 10, 0, 50, false, NodePanel.DESERT);
        nodes[3][6] = new NodePanel(10, 10, 0, 50, false, NodePanel.DESERT);
        nodes[3][7] = new NodePanel(10, 10, 0, 50, false, NodePanel.DESERT);
        nodes[3][8] = new NodePanel(10, 10, 0, 50, false, NodePanel.DESERT);
        nodes[3][9] = new NodePanel(80, 10, 0, 50, false, NodePanel.OCEAN);
        nodes[4][0] = new NodePanel(80, 10, 0, 50, false, NodePanel.OCEAN);
        nodes[4][1] = new NodePanel(80, 10, 0, 50, false, NodePanel.OCEAN);
        nodes[4][2] = new NodePanel(10, 10, 0, 50, false, NodePanel.DESERT);
        nodes[4][3] = new NodePanel(10, 10, 0, 50, false, NodePanel.DESERT);
        nodes[4][4] = new NodePanel(10, 10, 0, 50, false, NodePanel.DESERT);
        nodes[4][5] = new NodePanel(10, 10, 0, 50, false, NodePanel.DESERT);
        nodes[4][6] = new NodePanel(10, 10, 0, 50, false, NodePanel.DESERT);
        nodes[4][7] = new NodePanel(10, 10, 0, 50, false, NodePanel.DESERT);
        nodes[4][8] = new NodePanel(10, 10, 0, 50, false, NodePanel.DESERT);
        nodes[4][9] = new NodePanel(80, 10, 0, 50, false, NodePanel.OCEAN);
        nodes[5][0] = new NodePanel(80, 10, 0, 50, false, NodePanel.OCEAN);
        nodes[5][1] = new NodePanel(80, 10, 0, 50, false, NodePanel.OCEAN);
        nodes[5][2] = new NodePanel(10, 10, 0, 50, false, NodePanel.DESERT);
        nodes[5][3] = new NodePanel(10, 10, 0, 50, false, NodePanel.DESERT);
        nodes[5][4] = new NodePanel(10, 10, 0, 50, false, NodePanel.DESERT);
        nodes[5][5] = new NodePanel(10, 10, 0, 50, false, NodePanel.DESERT);
        nodes[5][6] = new NodePanel(10, 10, 0, 50, false, NodePanel.DESERT);
        nodes[5][7] = new NodePanel(10, 10, 0, 50, false, NodePanel.DESERT);
        nodes[5][8] = new NodePanel(10, 10, 0, 50, false, NodePanel.DESERT);
        nodes[5][9] = new NodePanel(80, 10, 0, 50, false, NodePanel.OCEAN);
        nodes[6][0] = new NodePanel(80, 10, 0, 50, false, NodePanel.OCEAN);
        nodes[6][1] = new NodePanel(80, 10, 0, 50, false, NodePanel.OCEAN);
        nodes[6][2] = new NodePanel(10, 10, 0, 50, false, NodePanel.DESERT);
        nodes[6][3] = new NodePanel(10, 10, 0, 50, false, NodePanel.DESERT);
        nodes[6][4] = new NodePanel(10, 10, 0, 50, false, NodePanel.DESERT);
        nodes[6][5] = new NodePanel(10, 10, 0, 50, false, NodePanel.FOREST);
        nodes[6][6] = new NodePanel(10, 10, 0, 50, false, NodePanel.DESERT);
        nodes[6][7] = new NodePanel(10, 10, 0, 50, false, NodePanel.DESERT);
        nodes[6][8] = new NodePanel(10, 10, 0, 50, false, NodePanel.DESERT);
        nodes[6][9] = new NodePanel(80, 10, 0, 50, false, NodePanel.OCEAN);
        nodes[7][0] = new NodePanel(80, 10, 0, 50, false, NodePanel.OCEAN);
        nodes[7][1] = new NodePanel(80, 10, 0, 50, false, NodePanel.OCEAN);
        nodes[7][2] = new NodePanel(10, 10, 0, 50, false, NodePanel.DESERT);
        nodes[7][3] = new NodePanel(10, 10, 0, 50, false, NodePanel.DESERT);
        nodes[7][4] = new NodePanel(10, 10, 0, 50, false, NodePanel.DESERT);
        nodes[7][5] = new NodePanel(10, 10, 0, 50, false, NodePanel.DESERT);
        nodes[7][6] = new NodePanel(10, 10, 0, 50, false, NodePanel.DESERT);
        nodes[7][7] = new NodePanel(10, 10, 0, 50, false, NodePanel.DESERT);
        nodes[7][8] = new NodePanel(10, 10, 0, 50, false, NodePanel.DESERT);
        nodes[7][9] = new NodePanel(80, 10, 0, 50, false, NodePanel.OCEAN);
        nodes[8][0] = new NodePanel(80, 10, 0, 50, false, NodePanel.OCEAN);
        nodes[8][1] = new NodePanel(80, 10, 0, 50, false, NodePanel.OCEAN);
        nodes[8][2] = new NodePanel(10, 10, 0, 50, false, NodePanel.DESERT);
        nodes[8][3] = new NodePanel(10, 10, 0, 50, false, NodePanel.DESERT);
        nodes[8][4] = new NodePanel(10, 10, 0, 50, false, NodePanel.DESERT);
        nodes[8][5] = new NodePanel(10, 10, 0, 50, false, NodePanel.DESERT);
        nodes[8][6] = new NodePanel(10, 10, 0, 50, false, NodePanel.DESERT);
        nodes[8][7] = new NodePanel(10, 10, 0, 50, false, NodePanel.DESERT);
        nodes[8][8] = new NodePanel(10, 10, 0, 50, false, NodePanel.DESERT);
        nodes[8][9] = new NodePanel(80, 10, 0, 50, false, NodePanel.OCEAN);
        nodes[9][0] = new NodePanel(80, 10, 0, 50, false, NodePanel.OCEAN);
        nodes[9][1] = new NodePanel(80, 10, 0, 50, false, NodePanel.OCEAN);
        nodes[9][2] = new NodePanel(80, 10, 0, 50, false, NodePanel.OCEAN);
        nodes[9][3] = new NodePanel(80, 10, 0, 50, false, NodePanel.OCEAN);
        nodes[9][4] = new NodePanel(80, 10, 0, 50, false, NodePanel.OCEAN);
        nodes[9][5] = new NodePanel(80, 10, 0, 50, false, NodePanel.OCEAN);
        nodes[9][6] = new NodePanel(80, 10, 0, 50, false, NodePanel.OCEAN);
        nodes[9][7] = new NodePanel(80, 10, 0, 50, false, NodePanel.OCEAN);
        nodes[9][8] = new NodePanel(80, 10, 0, 50, false, NodePanel.OCEAN);
        nodes[9][9] = new NodePanel(80, 10, 0, 50, false, NodePanel.OCEAN);

        for (int i = 0; i < nodes.length; i++) {
            for (int j = 0; j < nodes[i].length; j++) {
                f.add(nodes[i][j]);

            }

        }

        int delay = 1000; //milliseconds
        ActionListener taskPerformer = new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent evt) {
                f.repaint();
                for (int i = 0; i < wind.size(); i++) {
                    if (wind.get(i).life == 0) {
                        wind.remove(i);
                        i--;
                    } else {
                        wind.get(i).iterate();
                    }

                }
            }
        };
        new Timer(delay, taskPerformer).start();

    }
}