/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package nimbus;

import java.awt.Color;
import java.awt.Dimension;
import java.awt.Graphics;
import javax.swing.JPanel;

/**
 *
 * @author Wrench
 */
public class NodePanel extends JPanel{
    public static final int OCEAN = 0;
    public static final int DESERT = 1;
    public static final int MOUNTAIN = 2;
    public static final int PLAIN = 3;
    public static final int FOREST = 4;
    
    public static final int NORTH_DIR = 5;
    public static final int NORTHEAST_DIR = 6;
    public static final int EAST_DIR = 7;
    public static final int SOUTHEAST_DIR = 8;
    public static final int SOUTH_DIR = 9;
    public static final int SOUTHWEST_DIR = 10;
    public static final int WEST_DIR = 11;
    public static final int NORTHWEST_DIR = 12;
    
    public NodePanel north;
    public NodePanel northEast;
    public NodePanel east;
    public NodePanel southEast;
    public NodePanel south;
    public NodePanel southWest;
    public NodePanel west;
    public NodePanel northWest;
    
    float humidity;
    float groundWater;
    int elevation;
    float temperature = 50;
    float pressure;
    boolean flooded;
    int type;
    
    public Storm rain;

    public NodePanel(float humidity, float groundWater, int elevation, int pressure, boolean flooded, int type) {
        this.humidity = humidity;
        this.groundWater = groundWater;
        this.elevation = elevation;
        this.pressure = pressure;
        this.type = type;
        
        if(type == NodePanel.DESERT){
            temperature = 60;
        }
        if(type == NodePanel.PLAIN){
            temperature = 40;
        }
        if(type == NodePanel.FOREST){
            temperature = 35;
        }
    }
    
    
    public boolean hasStorm(){
        return rain != null;
    }//end
    
    public void destroyStorm(){
        rain = null;
    }

    
    public NodePanel Visit(int direction) {
        switch(direction){
            case NORTH_DIR: return north;
            case NORTHEAST_DIR: return northEast;
            case EAST_DIR: return east;
            case SOUTHEAST_DIR: return southEast;
            case SOUTH_DIR: return south;
            case SOUTHWEST_DIR: return southWest;
            case WEST_DIR: return west;
            case NORTHWEST_DIR: return northWest;
            default: return null;
        }
    }
    
    public void setNode(int direction, NodePanel node) {
        switch(direction){
            case NORTH_DIR: north = node; break;
            case NORTHEAST_DIR: northEast = node; break;
            case EAST_DIR: east = node; break;
            case SOUTHEAST_DIR: southEast = node; break;
            case SOUTH_DIR: south = node; break;
            case SOUTHWEST_DIR: southWest = node; break;
            case WEST_DIR: west = node; break;
            case NORTHWEST_DIR: northWest = node; break;
        }
    }

    
    public float getGroundWater() {
        return groundWater;
    }

    
    public float getHumidity() {
        return humidity;
    }

    
    public float getPressure() {
        return pressure;
    }

    
    public float getTemperature() {
        return temperature;
    }

    
    public boolean isFlooded() {
        return groundWater > 60;
    }

    
    public void setElevation(int elevation) {
        this.elevation = elevation;
    }

    
    public void setGroundWater(float groundWater) {
        this.groundWater = groundWater;
    }

    
    public void setHumidity(float humidity) {
        this.humidity = humidity;
    }

    
    public void setPressure(float pressure) {
        this.pressure = pressure;
    }

    
    public void setTemperature(float temperature) {
        this.temperature = temperature;
    }

    
    public int getElevation() {
        return elevation;
    }
    
    @Override
     public Dimension getPreferredSize() {
         
        return new Dimension(50,50);
    }

    
    @Override
    public void paintComponent(Graphics g) {
        super.paintComponent(g);
        
        if(groundWater > 20 && humidity < 40){
            groundWater-=0.2;
            humidity+=0.2;
        }

        if(type == NodePanel.DESERT){
            if(groundWater > 30){
                type=NodePanel.PLAIN;
                temperature = 40;
            }
            if(temperature < 60){
                temperature += Math.min(60-temperature, .1);
            }else if (temperature > 60){
                temperature -= Math.min(temperature-60, .1);
            }
            g.setColor(Color.yellow);
        }else if(type == NodePanel.OCEAN){
            setGroundWater(0);
            if(humidity <80){
                humidity+=1.3;
            }
            if(temperature < 50){
                temperature += Math.min(50-temperature, .1);
            }else if (temperature > 50){
                temperature -= Math.min(temperature-50, .1);
            }
            g.setColor(Color.blue);
        }else if(type == NodePanel.MOUNTAIN){
            g.setColor(Color.darkGray);
            if(temperature < 50){
                temperature += Math.min(50-temperature, .1);
            }else if (temperature > 50){
                temperature -= Math.min(temperature-50, .1);
            }
        }else if(type == NodePanel.PLAIN){
            g.setColor(Color.green);
            if(temperature < 40){
                temperature += Math.min(40-temperature, .1);
            }else if (temperature > 40){
                temperature -= Math.min(temperature-40, .1);
            }
        }else{
            g.setColor(Color.black);
        }
        g.fillRect(0, 0, 50, 50);
        
        if(humidity / (temperature * 2) > .85){
                rain = new Storm();
                rain.strength = 10;
                humidity -= 50;
            }
        
        if(isFlooded()){
            g.setColor(new Color((float)0.2, (float)0.2, (float)0.8, (float)0.8));
            g.fillRect(10, 10, 30, 30);
        }
        
        g.setColor(Color.black);
        g.drawRect(0, 0, 50, 50);
        
        g.setColor(Color.cyan);
        g.fillRect(3, 3, (int)(humidity/2), 5);
        
        g.setColor(Color.magenta);
        g.fillRect(3, 10, (int)(groundWater/2), 5);
        
        if(rain != null){
            g.setColor(Color.WHITE);
            g.fillOval(0, 0, 45, 45);
            g.setColor(Color.BLACK);
            g.fillRect(3, 17, rain.strength, 5);
        }
    }  
}//end NodePanel