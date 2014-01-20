/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package nimbus;

import java.util.ListIterator;
import java.util.Stack;

/**
 *
 * @author Wrench
 */
public class Wind {

    Stack<NodePanel> path = new Stack<>();
    int life;
    NodePanel current = null, next;
    boolean complete = false;

    public Wind(int life) {
        this.life = life;
    }

    public void add(NodePanel node) {
        path.push(node);
    }//end add

    public NodePanel peek() {
        return path.peek();
    }//end add

    //returns life left
    public int iterate() {
        if (!complete) {
            return -1;
        }
        ListIterator<NodePanel> nodes = path.listIterator(path.size());

        if (nodes.hasPrevious()) {
            current = nodes.previous();
        }
        while (nodes.hasPrevious()) {
            next = nodes.previous();

            if (next.humidity > 5 && next.humidity > current.humidity) {
                float change = Math.min(next.humidity / 5, 100 - current.humidity);
                current.humidity += change;
                next.humidity -= change;
            }
            if (next.type == NodePanel.MOUNTAIN && !current.hasStorm() && current.humidity > 60) {
                current.rain = new Storm();
                current.rain.strength = 10;
                current.humidity -= 40;
            }

            if (next.hasStorm()) {
                next.setGroundWater(next.getGroundWater() + 8);
                next.rain.strength -= 2;
                next.temperature -=5;
                if (next.getHumidity() >= 60 && next.rain.strength <= 10) {
                    next.rain.strength += next.getHumidity()/12;
                    if (next.rain.strength > 10) {
                        next.rain.strength = 10;
                    }//end if
                }//end if
                if (next.rain.strength > 0) {
                    current.rain = next.rain;
                }

                next.destroyStorm();
            }//end
            current = next;
        }//end while

        if (life != -1) {
            life--;
        }
        return life;
    }//end iterate
}//end Wind