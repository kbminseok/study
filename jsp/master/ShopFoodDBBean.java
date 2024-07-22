package master;

import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.util.ArrayList;
import java.util.List;
import javax.naming.Context;
import javax.naming.InitialContext;
import javax.sql.DataSource;

public class ShopFoodDBBean {
	
    private static ShopFoodDBBean instance 
                          = new ShopFoodDBBean();
    
    public static ShopFoodDBBean getInstance() {
        return instance;
    }
    
    private ShopFoodDBBean() {}
    
    //  커넥션풀로부터 커넥션객체를 얻어내는 메소드
    private Connection getConnection() throws Exception {
        Context initCtx = new InitialContext();
        Context envCtx = (Context) initCtx.lookup("java:comp/env");
        DataSource ds = (DataSource)envCtx.lookup("jdbc/basicjsp");
        return ds.getConnection();
    }
    
    //  관리자 인증 메소드
    public int managerCheck(String id, String passwd) 
	throws Exception {
		Connection conn = null;
        PreparedStatement pstmt = null;
		ResultSet rs= null;
        String dbpasswd="";
		int x=-1;
        
		try {
            conn = getConnection();
            
            pstmt = conn.prepareStatement(
            	"select managerPasswd from manager where managerId = ? ");
            pstmt.setString(1, id);
            
            rs= pstmt.executeQuery();

			if(rs.next()){
				dbpasswd= rs.getString("managerPasswd"); 
				if(dbpasswd.equals(passwd))
					x= 1; //인증 성공
				else
					x= 0; //비밀번호 틀림
			}else
				x= -1;//해당 아이디 없음
			
        } catch(Exception ex) {
            ex.printStackTrace();
        } finally {
			if (rs != null) 
				try { rs.close(); } catch(SQLException ex) {}
            if (pstmt != null) 
            	try { pstmt.close(); } catch(SQLException ex) {}
            if (conn != null) 
            	try { conn.close(); } catch(SQLException ex) {}
        }
		return x;
	}
    
    //책 등록 메소드
    public void insertFood(ShopFoodDataBean food) 
    throws Exception {
        Connection conn = null;
        PreparedStatement pstmt = null;
        
        try {
            conn = getConnection();
            
            pstmt = conn.prepareStatement(
            	"insert into food values (?,?,?,?,?,?)");
            pstmt.setInt(1,food.getFood_id());
            pstmt.setString(2, food.getFood_kind());
            pstmt.setString(3, food.getFood_name());
            pstmt.setInt(4, food.getFood_price());
            pstmt.setShort(5, food.getFood_count());
			pstmt.setString(6, food.getFood_image());
			
            pstmt.executeUpdate();
            
        } catch(Exception ex) {
            ex.printStackTrace();
        } finally {
            if (pstmt != null) 
            	try { pstmt.close(); } catch(SQLException ex) {}
            if (conn != null) 
            	try { conn.close(); } catch(SQLException ex) {}
        }
    }
        
	// 전체등록된 책의 수를 얻어내는 메소드
	public int getFoodCount()
    throws Exception {
        Connection conn = null;
        PreparedStatement pstmt = null;
        ResultSet rs = null;

        int x=0;

        try {
            conn = getConnection();
            
            pstmt = conn.prepareStatement("select count(*) from food");
            rs = pstmt.executeQuery();

            if (rs.next()) 
               x= rs.getInt(1);
        } catch(Exception ex) {
            ex.printStackTrace();
        } finally {
            if (rs != null) 
            	try { rs.close(); } catch(SQLException ex) {}
            if (pstmt != null) 
            	try { pstmt.close(); } catch(SQLException ex) {}
            if (conn != null) 
            	try { conn.close(); } catch(SQLException ex) {}
        }
		return x;
    }
	
	// 분류별또는 전체등록된 책의 정보를 얻어내는 메소드
	public List<ShopFoodDataBean> getFoods(String food_kind)
    throws Exception {
        Connection conn = null;
        PreparedStatement pstmt = null;
        ResultSet rs = null;
        List<ShopFoodDataBean> foodList=null;
        
        try {
            conn = getConnection();
            
            String sql1 = "select * from food";
            String sql2 = "select * from food ";
            sql2 += "where food_kind  = ? order by food_id desc";//등록일자 내림차순 다른걸로 수정해야함
            
            if(food_kind.equals("all")){
            	 pstmt = conn.prepareStatement(sql1);
            }else{
                pstmt = conn.prepareStatement(sql2);
                pstmt.setString(1, food_kind);
            }
        	rs = pstmt.executeQuery();
            
            if (rs.next()) {
                foodList = new ArrayList<ShopFoodDataBean>();
                do{
                     ShopFoodDataBean food= new ShopFoodDataBean();
                     
                     food.setFood_id(rs.getInt("food_id"));
                     food.setFood_kind(rs.getString("food_kind"));
                     food.setFood_name(rs.getString("food_name"));
                     food.setFood_price(rs.getInt("food_price"));
                     food.setFood_count(rs.getShort("food_count"));
                     food.setFood_image(rs.getString("food_image"));
                     
                     foodList.add(food);
			    }while(rs.next());
			}
        } catch(Exception ex) {
            ex.printStackTrace();
        } finally {
            if (rs != null) 
            	try { rs.close(); } catch(SQLException ex) {}
            if (pstmt != null) 
            	try { pstmt.close(); } catch(SQLException ex) {}
            if (conn != null) 
            	try { conn.close(); } catch(SQLException ex) {}
        }
		return foodList;
    }
	
	// 쇼핑몰 메인에 표시하기 위해서 사용하는 분류별 신간책목록을 얻어내는 메소드
	public ShopFoodDataBean[] getFoods(String food_kind,int count)
    throws Exception {
        Connection conn = null;
        PreparedStatement pstmt = null;
        ResultSet rs = null;
        ShopFoodDataBean foodList[]=null;
        int i=0;
        
        try {
            conn = getConnection();
            
            String sql = "select * from food where food_kind=?";
            sql += "order by food_id desc limit ?,?";
            
            pstmt = conn.prepareStatement(sql);
            pstmt.setString(1, food_kind);
            pstmt.setInt(2, 0);
            pstmt.setInt(3, count);
        	rs = pstmt.executeQuery();

            if (rs.next()) {
                foodList = new ShopFoodDataBean[count];
                do{
                     ShopFoodDataBean food= new ShopFoodDataBean();
                     food.setFood_id(rs.getInt("food_id"));
                     food.setFood_kind(rs.getString("food_kind"));
                     food.setFood_name(rs.getString("food_name"));
                     food.setFood_price(rs.getInt("food_price"));
                     food.setFood_count(rs.getShort("food_count"));
                     food.setFood_image(rs.getString("food_image"));
                     
                     foodList[i]=food;
                     
                     i++;
			    }while(rs.next());
			}
        } catch(Exception ex) {
            ex.printStackTrace();
        } finally {
            if (rs != null) 
            	try { rs.close(); } catch(SQLException ex) {}
            if (pstmt != null) 
            	try { pstmt.close(); } catch(SQLException ex) {}
            if (conn != null) 
            	try { conn.close(); } catch(SQLException ex) {}
        }
		return foodList;
    }
	
	// foodId에 해당하는 책의 정보를 얻어내는 메소드로 
    //등록된 책을 수정하기 위해 수정폼으로 읽어들기이기 위한 메소드
	public ShopFoodDataBean getFood(int foodId)
    throws Exception {
        Connection conn = null;
        PreparedStatement pstmt = null;
        ResultSet rs = null;
        ShopFoodDataBean food=null;
        
        try {
            conn = getConnection();
            
            pstmt = conn.prepareStatement(
            	"select * from food where food_id = ?");
            pstmt.setInt(1, foodId);
            
            rs = pstmt.executeQuery();

            if (rs.next()) {
                food = new ShopFoodDataBean();
                
                food.setFood_kind(rs.getString("food_kind"));
                food.setFood_name(rs.getString("food_name"));
                food.setFood_price(rs.getInt("food_price"));
                food.setFood_count(rs.getShort("food_count"));
                food.setFood_image(rs.getString("food_image"));
			}
        } catch(Exception ex) {
            ex.printStackTrace();
        } finally {
            if (rs != null) 
            	try { rs.close(); } catch(SQLException ex) {}
            if (pstmt != null) 
            	try { pstmt.close(); } catch(SQLException ex) {}
            if (conn != null) 
            	try { conn.close(); } catch(SQLException ex) {}
        }
		return food;
    }
    
    // 등록된 책의 정보를 수정시 사용하는 메소드
    public void updateFood(ShopFoodDataBean food, int foodId)
    throws Exception {
        Connection conn = null;
        PreparedStatement pstmt = null;
        String sql;
        
        try {
            conn = getConnection();
            
            sql = "update food set food_kind=?,food_name=?,food_price=?";
            sql += ",food_count=?";
            sql += ",food_image=?";
            sql += " where food_id=?";
            
            pstmt = conn.prepareStatement(sql);
            
            pstmt.setString(1, food.getFood_kind());
            pstmt.setString(2, food.getFood_name());
            pstmt.setInt(3, food.getFood_price());
            pstmt.setShort(4, food.getFood_count());
            //pstmt.setString(5, food.getAuthor());
            //pstmt.setString(6, food.getPublishing_com());
			//pstmt.setString(7, food.getPublishing_date());
			pstmt.setString(5, food.getFood_image());
			//pstmt.setString(9, food.getFood_content());
			//pstmt.setByte(10, food.getDiscount_rate());
			pstmt.setInt(6, foodId);
            
            pstmt.executeUpdate();
            
        } catch(Exception ex) {
            ex.printStackTrace();
        } finally {
            if (pstmt != null) 
            	try { pstmt.close(); } catch(SQLException ex) {}
            if (conn != null) 
            	try { conn.close(); } catch(SQLException ex) {}
        }
    }
    
    // foodId에 해당하는 책의 정보를 삭제시 사용하는 메소드
    public void deleteFood(int foodId)
    throws Exception {
        Connection conn = null;
        PreparedStatement pstmt = null;
        ResultSet rs= null;
        
        try {
			conn = getConnection();

            pstmt = conn.prepareStatement(
            	"delete from food where food_id=?");
            pstmt.setInt(1, foodId);
            
            pstmt.executeUpdate();
            
        } catch(Exception ex) {
            ex.printStackTrace();
        } finally {
            if (rs != null) 
            	try { rs.close(); } catch(SQLException ex) {}
            if (pstmt != null) 
            	try { pstmt.close(); } catch(SQLException ex) {}
            if (conn != null) 
            	try { conn.close(); } catch(SQLException ex) {}
        }
    }
}