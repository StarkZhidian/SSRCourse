import java.lang.reflect.InvocationTargetException;

public enum TestEnum {
	X("x"), Y("y"), Z("z");

	private String value;

	TestEnum(String value) {
		this.value = value;
	}

    public String getValue() {
		return value;
	}

	public static TestEnum reflectInstance() {
		try {
			return TestEnum.class.getDeclaredConstructor(String.class, int.class, String.class)
					.newInstance("123", 1, "123");
		} catch (Exception e) {
			e.printStackTrace();
		}
		return null;
	}
}