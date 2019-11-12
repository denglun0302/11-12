public class M1AndM2 {
    public volatile static int n  = 0;

    private static void add() {
        n++;
    }

    private static void sub() {
        n--;
    }

    private static class MyThread extends Thread {
        @Override
        public void run() {
            for (int i = 0; i < 10_0000; i++) {
                add();
            }
        }
    }

    public static void main(String[] args) throws InterruptedException {
        Thread thread = new MyThread();
        thread.start();
        for (int i = 0; i < 10_0000; i++) {
            sub();
        }
        thread.join();
        System.out.println(n);
    }
}
