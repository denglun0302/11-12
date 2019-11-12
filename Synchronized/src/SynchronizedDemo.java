

public class SynchronizedDemo {
    public synchronized void method(){
        for(int i=0;i<100000;i++){
            System.out.println(Thread.currentThread().getName());
        }
    }
    public synchronized void method2(){
        for(int i=0;i<100000;i++){
            System.out.println(Thread.currentThread().getName());
        }
    }
    public synchronized  static void staticmethod() {
    }
    public void block(){
        synchronized (SynchronizedDemo.class){

        }
        synchronized (SynchronizedDemo.class){

        }
    }
    private static class myThread extends Thread{
        @Override
        public void run(){
            while(true){
                object.method();
            }
        }
        private SynchronizedDemo object;
       void MyThread(SynchronizedDemo object){
            this.object=new SynchronizedDemo();
        }
    }

    public static void main(String[] args) {

        SynchronizedDemo object=new  SynchronizedDemo();
        Thread t=new myThread();
        t.start();
        while(true){
            object.method2();
        }
    }

}
