package master;

public class ShopFoodDataBean {
	private int food_id; //책의 등록번호
	private String food_kind; //책의 분류
	private String food_name; //책이름
	private int food_price; //책가격
	private short food_count; //책의 재고수량
	private String food_image; //책이미지명
	
	public int getFood_id() {
		return food_id;
	}
	public void setFood_id(int food_id) {
		this.food_id = food_id;
	}
	public String getFood_kind() {
		return food_kind;
	}
	public void setFood_kind(String food_kind) {
		this.food_kind = food_kind;
	}
	public String getFood_name() {
		return food_name;
	}
	public void setFood_name(String food_name) {
		this.food_name = food_name;
	}
	public int getFood_price() {
		return food_price;
	}
	public void setFood_price(int food_price) {
		this.food_price = food_price;
	}
	public short getFood_count() {
		return food_count;
	}
	public void setFood_count(short food_count) {
		this.food_count = food_count;
	}
	public String getFood_image() {
		return food_image;
	}
	public void setFood_image(String food_image) {
		this.food_image = food_image;
	}

}