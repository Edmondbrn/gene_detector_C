import java.util.ArrayList;

public class test_array {



    public static void main(String[] args) {
        
        ArrayList<Integer> test = new ArrayList<>();

        long start = System.currentTimeMillis();
        for (int i = 0;  i < 100000; i++)
            test.add(i);
        System.out.println((System.currentTimeMillis() - start));

    }


}