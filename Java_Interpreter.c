//package interpreter;

import java.io.BufferedReader;
import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;
import java.io.PrintWriter;
import java.util.HashMap;
import java.util.Map;
import java.util.Stack;

public class interpreter {
    /*public static void main(String[] args) throws NumberFormatException, IOException{
        interpreter("C:/Users/Robert/Desktop/input.txt","C:/Users/Robert/Desktop/output.txt");
    }*/
    
    public static void interpreter(String input, String output) throws NumberFormatException, IOException{
        File file = new File(input);
        BufferedReader br = new BufferedReader(new FileReader(file));
        PrintWriter w = new PrintWriter(output);
        Stack<String> s = new Stack<String>();
        Map<String, String> bindmap = new HashMap();
        try{
            String line = "";
            while((line = br.readLine()) != null){
                String k = line.replaceAll(" ", "");
                String k2 = line.replaceAll("[^A-Za-z]", "");
                if(k2.contains("push") == true && k2.equals("push") == false){
                    k2 = "push";
                }
                switch (k2) {
                    case "push": 
                        int indexOfLast = k.indexOf("h");
                        String n = k;
                        if(indexOfLast >= 0) n = k.substring(indexOfLast + 1, k.length());
                        String r = n.replace("\"", "");
                        if(isintornot(r) == true || isNumeric(r) == true){
                            String d = isdoubleornot(r);
                            if(d.contentEquals("-0")){
                                s.push("0");
                            }
                            else{
                                s.push(d);
                            }
                        }
                        else{
                            int xxx = line.indexOf("h");
                            if(line.contains("-") == true){
                                s.push(":error:");
                            }
                            else{
                                s.push(line.substring(xxx + 2, line.length()).replace("\"", ""));
                            }
                        }
                        break;
                    case "pop":
                        if(s.isEmpty() == true){
                            s.push(":error:");
                        }
                        else{
                            s.pop();
                        }
                        break;
                    case "true":
                        s.push(":true:");
                        break;
                    case "false":
                        s.push(":false:");
                        break;
                    case "error":
                        s.push(":error:");
                        break;
                    case "add": 
                        if(s.isEmpty() == true || s.size() == 1){
                            s.push(":error:");
                        }
                        else if(k.contains(".")){
                            s.push(":error:");
                        }
                        else{
                            String u = s.peek();
                            if(bindmap.containsKey(u) == true){
                                u = bindmap.get(u);
                            }
                            s.pop();
                            String o = s.peek();
                            if(bindmap.containsKey(o) == true){
                                o = bindmap.get(o);
                            }
                            s.pop();
                            if(isNumeric(u) == true){
                                int h = Integer.parseInt(u);
                                if(isNumeric(o) == true){
                                    int g = Integer.parseInt(o);
                                    int y = h + g;
                                    String l = String.valueOf(y);
                                    s.push(l);
                                }
                                else{
                                    s.push(o);
                                    s.push(u);
                                    s.push(":error:");
                                }
                            }
                            else{
                                s.push(o);
                                s.push(u);
                                s.push(":error:");
                            }
                        
                        }
                        break;
                    case "sub":
                        if(s.isEmpty() == true || s.size() == 1){
                            s.push(":error:");
                        }
                        else if(k.contains(".")){
                            s.push(":error:");
                        }
                        else{
                            String u = s.peek();
                            if(bindmap.containsKey(u) == true){
                                u = bindmap.get(u);
                            }
                            if(isNumeric(u) == true){
                                s.pop();
                                String o = s.peek();
                                if(bindmap.containsKey(o) == true){
                                    o = bindmap.get(o);
                                }
                                if(isNumeric(o) == true){
                                    s.pop();
                                    int h = Integer.parseInt(u);
                                    int g = Integer.parseInt(o);
                                    int y = g - h;
                                    String b = String.valueOf(y);
                                    s.push(b);
                                }
                                else{
                                    s.push(u);
                                    s.push(":error:");
                                }
                            }
                            else{
                                s.push(":error:");
                            }
                        }
                        break;
                    case "mul":
                        if(s.isEmpty() == true || s.size() == 1){
                            s.push(":error:");
                        }
                        else if(k.contains(".")){
                            s.push(":error:");
                        }
                        else{
                            String u = s.peek();
                            if(bindmap.containsKey(u) == true){
                                u = bindmap.get(u);
                            }
                            if(isNumeric(u) == true){
                                s.pop();
                                String o = s.peek();
                                if(bindmap.containsKey(o) == true){
                                    o = bindmap.get(o);
                                }
                                if(isNumeric(o) == true){
                                    s.pop();
                                    int h = Integer.parseInt(u);
                                    int g = Integer.parseInt(o);
                                    int y = h * g;
                                    String a = String.valueOf(y);
                                    s.push(a);
                                }
                                else{
                                    s.push(u);
                                    s.push(":error:");
                                }
                            }
                            else{
                                s.push(":error:");
                            }
                        }
                        break;
                    case "div":
                        if(s.isEmpty() == true || s.size() == 1){
                            s.push(":error:");
                        }
                        else if(k.contains(".")){
                            s.push(":error:");
                        }
                        else{
                            String u = s.peek();
                            if(bindmap.containsKey(u) == true){
                                u = bindmap.get(u);
                            }
                            s.pop();
                            String o = s.peek();
                            if(bindmap.containsKey(o) == true){
                                o = bindmap.get(o);
                            }
                            s.pop();
                            if(isNumeric(u) == true){
                                int h = Integer.parseInt(u);
                                if(isNumeric(o) == true){
                                    int g = Integer.parseInt(o);
                                    if(h == 0){
                                        s.add(o);
                                        s.add(u);
                                        s.push(":error:");
                                    }
                                    else{
                                        int y = g / h;
                                        if(isdoubleornot2(String.valueOf(y)) == false){
                                            s.push("0");
                                        }
                                        String p = String.valueOf(y);
                                        s.push(p);
                                    }
                                }
                            }
                            else{
                                s.push(o);
                                s.push(u);
                                s.push(":error:");
                            }
                        }
                        break;
                    case "rem":
                        if(s.isEmpty() == true || s.size() == 1){
                            s.push(":error:");
                        }
                        else if(k.contains(".")){
                            s.push(":error:");
                        }
                        else{
                            String u = s.peek();
                            if(bindmap.containsKey(u) == true){
                                u = bindmap.get(u);
                            }
                            s.pop();
                            String o = s.peek();
                            if(bindmap.containsKey(o) == true){
                                o = bindmap.get(o);
                            }
                            s.pop();
                            if(isNumeric(u) == true){
                                int h = Integer.parseInt(u);
                                if(isNumeric(o) == true){
                                    int g = Integer.parseInt(o);
                                    int y = g % h;
                                    String i = String.valueOf(y);
                                    s.push(i);
                                }
                            }
                            else{
                                s.push(o);
                                s.push(u);
                                s.push(":error:");
                            }
                        }
                        break;
                    case "neg":
                        if(s.isEmpty() == true){
                            s.push(":error:");
                        }
                        else if(k.contains(".")){
                            s.push(":error:");
                        }
                        else{
                            String u = s.peek();
                            if(bindmap.containsKey(u) == true){
                                u = bindmap.get(u);
                            }
                            s.pop();
                            if(isNumeric(u) == true){
                                int h = Integer.parseInt(u);
                                h = h * -1;
                                String q = String.valueOf(h);
                                s.push(q);
                            }
                            else{
                                s.push(u);
                                s.push(":error:");
                            }
                        }
                        break;
                    case "swap":
                        if(s.isEmpty() == true || s.size() == 1){
                            s.push(":error:");
                        }
                        else if(k.contains(".")){
                            s.push(":error:");
                        }
                        else{
                            String u = s.peek();
                            s.pop();
                            String o = s.peek();
                            s.pop();
                            s.push(u);
                            s.push(o);
                        }
                        break;
                    case "and":
                        if(s.isEmpty() == true || s.size() == 1){
                            s.push(":error:");
                        }
                        else if(k.contains(".")){
                            s.push(":error:");
                        }
                        else{
                            String u = s.peek();
                            if(bindmap.containsKey(u) == true){
                                u = bindmap.get(u);
                            }
                            if(u.equals(":true:") || u.equals(":false:")){
                                s.pop();
                                String o = s.peek();
                                if(bindmap.containsKey(o) == true){
                                    o = bindmap.get(o);
                                }
                                if(o.equals(":true:") || o.equals(":false:")){
                                    s.pop();
                                    if(u.equals(":true:") && o.equals(":true:") || o.equals(":true:") && u.equals(":true:")){
                                        s.push(":true:");
                                    }
                                    else if(u.equals(":false:") && o.equals(":false:") || o.equals(":false:") && u.equals(":false:")){
                                        s.push(":true:");
                                    }
                                    else{
                                        s.push(":false:");
                                    }
                                }
                                else{
                                    s.push(u);
                                    s.push(":error:");
                                }
                            }
                            else if(bindmap.size() != 0){
                                if(bindmap.get(u).equals(":true:") || bindmap.get(u).equals(":false:")){
                                    s.pop();
                                    String o = s.peek();
                                    if(bindmap.containsKey(o) == true){
                                        o = bindmap.get(o);
                                    }
                                    if(o.equals(":true:") || o.equals(":false:")){
                                        s.pop();
                                        if(u.equals(":true:") && o.equals(":true:") || o.equals(":true:") && u.equals(":true:") || bindmap.get(u).equals(":true:") && o.equals(":true:") || o.equals(":true:") && bindmap.get(u).equals(":true:")){
                                            s.push(":true:");
                                        }
                                        else if(u.equals(":false:") && o.equals(":false:") || o.equals(":false:") && u.equals(":false:") || bindmap.get(u).equals(":false:") && o.equals(":false:") || o.equals(":false:") && bindmap.get(u).equals(":false:")){
                                            s.push(":true:");
                                        }
                                        else{
                                            s.push(":false:");
                                        }
                                    }
                                    else{
                                        s.push(u);
                                        s.push(":error:");
                                    }
                                }
                            }
                            else{
                                s.push(":error:");
                            }
                        }
                        break;
                    case "or":
                        if(s.isEmpty() == true || s.size() == 1){
                            s.push(":error:");
                        }
                        else if(k.contains(".")){
                            s.push(":error:");
                        }
                        else{
                            String u = s.peek();
                            if(bindmap.containsKey(u) == true){
                                u = bindmap.get(u);
                            }
                            if(u.equals(":true:") || u.equals(":false:")){
                                s.pop();
                                String o = s.peek();
                                if(bindmap.containsKey(o) == true){
                                    o = bindmap.get(o);
                                }
                                if(o.equals(":true:") || o.equals(":false:")){
                                    s.pop();
                                    if(u.equals(":true:") || o.equals(":true:")){
                                        s.push(":true:");
                                    }
                                    else{
                                        s.push(":false:");
                                    }
                                }
                                else{
                                    s.push(u);
                                    s.push(":error:");
                                }
                            }
                            else{
                                s.push(":error:");
                            }
                        }
                        break;
                    case "not":
                        if(s.isEmpty() == true || s.size() == 0){
                            s.push(":error:");
                        }
                        else if(k.contains(".")){
                            s.push(":error:");
                        }
                        else{
                            String u = s.peek();
                            if(bindmap.containsKey(u) == true){
                                u = bindmap.get(u);
                            }
                            if(u.equals(":true:") || u.equals(":false:")){
                                s.pop();
                                if(u.equals(":true:")){
                                    s.push(":false:");
                                }
                                else if(u.equals(":false:")){
                                    s.push(":true:");
                                }
                            }
                            else{
                                s.push(":error:");
                            }
                        }
                        break;
                    case "equal":
                        if(s.isEmpty() == true || s.size() == 1){
                            s.push(":error:");
                        }
                        else if(k.contains(".")){
                            s.push(":error:");
                        }
                        else{
                            String u = s.peek();
                            if(bindmap.containsKey(u) == true){
                                u = bindmap.get(u);
                            }
                            if(isNumeric(u) == true){
                                s.pop();
                                String o = s.peek();
                                if(bindmap.containsKey(o) == true){
                                    o = bindmap.get(o);
                                }
                                if(isNumeric(o) == true){
                                    s.pop();
                                    if(u == o){
                                        s.push(":true:");
                                    }
                                    else{
                                        s.push(":false:");
                                    }
                                }
                                else{
                                    s.push(u);
                                    s.push(":error:");
                                }
                            }
                            else{
                                s.push(":error:");
                            }
                        }
                        break;
                    case "lessThan":
                        if(s.isEmpty() == true || s.size() == 1){
                            s.push(":error:");
                        }
                        else if(k.contains(".")){
                            s.push(":error:");
                        }
                        else{
                            String u = s.peek();
                            if(bindmap.containsKey(u) == true){
                                u = bindmap.get(u);
                            }
                            if(isNumeric(u) == true){
                                s.pop();
                                String o = s.peek();
                                if(bindmap.containsKey(o) == true){
                                    o = bindmap.get(o);
                                }
                                if(isNumeric(o) == true){
                                    s.pop();
                                    int h = Integer.parseInt(u);
                                    int g = Integer.parseInt(o);
                                    if(g < h){
                                        s.push(":true:");
                                    }
                                    else{
                                        s.push(":false:");
                                    }
                                }
                                else{
                                    s.push(u);
                                    s.push(":error:");
                                }
                            }
                            else{
                                s.push(":error:");
                            }
                        }
                        break;
                    case "bind":
                        if(s.isEmpty() == true || s.size() == 1){
                            s.push(":error:");
                        }
                        else if(k.contains(".")){
                            s.push(":error:");
                        }
                        else{
                            String u = s.peek();
                            s.pop();
                            String o = s.peek();
                            s.pop();
                            if(u.equals(":error:") || o.equals(":error:")){
                                s.push(o);
                                s.push(u);
                                s.push(":error:");
                            }
                            else if(bindmap.containsKey(o) == true){
                                bindmap.remove(o);
                                bindmap.put(o, u);
                                s.push(":unit:");
                            }
                            else if(o.contains("-") == true){
                                s.push(":error:");
                                s.push(u);
                            }
                            else{
                                bindmap.put(o, u);
                                s.push(":unit:");
                            }
                        }        
                        break;
                    case "if":
                        if(s.isEmpty() == true || s.size() < 3){
                            s.push(":error:");
                        }
                        else if(k.contains(".")){
                            s.push(":error:");
                        }
                        else{
                            String x = s.peek();
                            if(bindmap.containsKey(x) == true){
                                x = bindmap.get(x);
                            }
                            s.pop();
                            String y = s.peek();
                            if(bindmap.containsKey(y) == true){
                                y = bindmap.get(y);
                            }
                            s.pop();
                            String z = s.peek();
                            if(bindmap.containsKey(z) == true){
                                z = bindmap.get(z);
                            }
                            if(z.equals(":true:") || z.equals(":false:")){
                                s.pop();
                                if(z.equals(":true:")){
                                    s.push(x);
                                }
                                if(z.equals(":false:")){
                                    s.push(y);
                                }
                            }
                            else{
                                s.push(":error:");
                            }
                        }
                        break;
                    case "let":
                        s.push("let");
                        break;
                    case "end":
                        if(s.isEmpty() == true || s.size() > 3){
                            s.push(":error:");
                        }
                        else if(k.contains(".")){
                            s.push(":error:");
                        }
                        else{
                            String u = s.peek();
                            s.pop();
                            String o = "";
                            int y = 0;
                            while(y == 0){
                                o = s.peek();
                                if(o.equals("let")){
                                    s.pop();
                                    s.push(u);
                                    y++;
                                }
                                else{
                                    s.pop();
                                }
                            }
                        }
                        break;
                }
            }
            while(s.isEmpty() != true){
                w.println(s.peek());
                s.pop();
            }
        }catch(FileNotFoundException e){
            e.printStackTrace();
        }
        w.close();
    }
    public static String isdoubleornot(String z){
        try{
            double d = Double.valueOf(z);
            if(d == (int) d){
                return z;
            }
            else{
                return ":error:";
            }
        } catch(Exception e){
            return null;
        }
    }
    public static boolean isdoubleornot2(String z){
        try{
            double d = Double.valueOf(z);
            if(d == (int) d){
                return true;
            }
            else{
                return false;
            }
        } catch(Exception e){
            return true;
        }
    }
    public static boolean isintornot(String z){
        try
         {
             Integer.parseInt(z);
             return true;
         }
         catch(NumberFormatException nfe)
         {
             return false;
         }
    }
    public static boolean isNumeric(String str) {  
      try  
      {  
        double d = Double.parseDouble(str);  
      }  
      catch(NumberFormatException nfe)  
      {  
        return false;  
      }  
      return true;  
    }
}