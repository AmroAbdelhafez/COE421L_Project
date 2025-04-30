import jssc.SerialPort;
import jssc.SerialPortException;

public class Driver {
    public static void main(String[] args) {
        SerialPort sp = new SerialPort("/dev/cu.usbserial-DN02MSGP"); 

        try {
            sp.openPort();
            sp.setParams(9600, 8, 1, 0);
            System.out.println("System ready. Press button to start!");

            while(true) {
                String line = readLine(sp);
                
                if(line.startsWith("COUNTDOWN:")) {
                    System.out.println("Game starting in " + line.split(":")[1] + " second(s)");
                }
                else if(line.startsWith("ROUND:")) {
                    System.out.println("\n=== ROUND " + line.split(":")[1] + " ===");
                }
                else if(line.startsWith("PRESSED:")) {
                    int sensor = Integer.parseInt(line.split(":")[1]);
                    System.out.println("Sensor " + sensor + " pressed");
                }
                else if(line.equals("GAME_OVER")) {
                    System.out.println("GAME OVER! Press button to restart");
                }
                else if(line.equals("SYSTEM_READY")) {
                    System.out.println("System initialized successfully");
                }
            }
        } catch(Exception e) {
            e.printStackTrace();
        }
    }

    private static String readLine(SerialPort sp) throws SerialPortException {
        StringBuilder sb = new StringBuilder();
        while(true) {
            byte[] b = sp.readBytes(1);
            if(b == null) continue;
            char c = (char)b[0];
            if(c == '\n') break;
            sb.append(c);
        }
        return sb.toString().trim();
    }
}
