public class StaticTypeMethod {

    public static <T> T getObj() {
        return (T) new Object();
    }

    public static void main(String[] args) {
        String s = getObj();
    }
}
