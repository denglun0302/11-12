public class StaticMethod {
    public synchronized static void method() {
        for (int i = 0; i < 100000; i++) {
            System.out.println(Thread.currentThread().getName());
        }
    }

    private static class myThread extends Thread {
        @Override
        public void run() {
            while (true) {
                StaticMethod.method();
            }
        }
    }

    public static void main(String[] args) {

        Thread t=new myThread();
        t.start();
        while(true){
            StaticMethod.method();
        }
    }
    }

