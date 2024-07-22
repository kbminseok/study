drop table member;
drop table manager;
drop table food;
drop table cart;
drop table buy;



--회원 테이블--
create table member(
id varchar(50) not null primary key,
passwd varchar(16) not null,
name varchar(10) not null,
email varchar(25) not null,
address varchar(100) not null,
tel varchar(20) not null
);

--매니저 테이블--
create table manager(
managerId varchar(50) not null primary key,
managerPasswd varchar(16) not null
);

--음식(상품) 테이블--
create table food(
food_id int not null primary key auto_increment,
food_kind varchar(30) not null,
food_name varchar(100) not null,
food_price int not null,
food_count smallint not null,
food_image varchar(30)
);

--장바구니 테이블--
create table cart(
cart_id int not null primary key auto_increment,
buyer varchar(50) not null,
food_id int not null,
food_name varchar(100) not null,
buy_price int not null,
buy_count tinyint not null,
food_image varchar(30)
);

--구매 테이블--
create table buy(
buy_id bigint not null,
buyer varchar(50) not null,
food_id int not null,
food_name varchar(100) not null,
buy_price int not null,
buy_count tinyint not null,
food_image varchar(30),
buy_date datetime not null,
deliveryAddress varchar(100) not null
);

--insert food--
INSERT INTO food (food_id, food_kind, food_name, food_price, food_count,food_image) 
VALUES (1, '100', '한우곱창전골', 13800, 50,'ko1.png');
INSERT INTO food (food_id, food_kind, food_name, food_price, food_count,food_image) 
VALUES (2, '100', '전복미역국', 14000, 50,'ko2.png');
INSERT INTO food (food_id, food_kind, food_name, food_price, food_count,food_image) 
VALUES (3, '100', '돼지김치찌개', 5300, 50,'ko3.png');

INSERT INTO food (food_id, food_kind, food_name, food_price, food_count,food_image) 
VALUES (4, '200', '마유유마라탕', 15900, 50,'ch1.png');
INSERT INTO food (food_id, food_kind, food_name, food_price, food_count,food_image) 
VALUES (5, '200', '대가간짜장', 10800, 50,'ch2.png');
INSERT INTO food (food_id, food_kind, food_name, food_price, food_count,food_image) 
VALUES (6, '200', '연경치킨꿔바로우', 13900, 50,'ch3.png');

INSERT INTO food (food_id, food_kind, food_name, food_price, food_count,food_image) 
VALUES (7, '300', '밀푀유나베', 14900, 50,'jp1.png');
INSERT INTO food (food_id, food_kind, food_name, food_price, food_count,food_image) 
VALUES (8, '300', '해물오코노미야끼', 13900, 50,'jp2.png');
INSERT INTO food (food_id, food_kind, food_name, food_price, food_count,food_image) 
VALUES (9, '300', '가츠동', 16900, 50,'jp3.png');

INSERT INTO food (food_id, food_kind, food_name, food_price, food_count,food_image) 
VALUES (10, '400', '봉골레크림빠네', 12900, 50,'us1.png');
INSERT INTO food (food_id, food_kind, food_name, food_price, food_count,food_image) 
VALUES (11, '400', '프레시지감바스', 13900, 50,'us2.png');
INSERT INTO food (food_id, food_kind, food_name, food_price, food_count,food_image) 
VALUES (12, '400', '토마토파스타', 12480, 50,'us3.png');

INSERT INTO food (food_id, food_kind, food_name, food_price, food_count,food_image) 
VALUES (13, '500', '캠핑닭튀김', 49900, 50,'ci.png');
INSERT INTO food (food_id, food_kind, food_name, food_price, food_count,food_image) 
VALUES (14, '500', '양념닭강정', 21900, 50,'ci1.png');
INSERT INTO food (food_id, food_kind, food_name, food_price, food_count,food_image) 
VALUES (15, '500', '버팔로치킨봉', 13400, 50,'ci2.png');

INSERT INTO food (food_id, food_kind, food_name, food_price, food_count,food_image) 
VALUES (16, '600', '조조칼국수', 17000, 50,'n1.png');
INSERT INTO food (food_id, food_kind, food_name, food_price, food_count,food_image) 
VALUES (17, '600', '냉소바', 9500, 50,'n2.png');
INSERT INTO food (food_id, food_kind, food_name, food_price, food_count,food_image) 
VALUES (18, '600', '들기름막국수', 19000, 50,'n3.png');

INSERT INTO food (food_id, food_kind, food_name, food_price, food_count,food_image) 
VALUES (19, '700', '캠핑군만두', 8900, 50,'m1.png');
INSERT INTO food (food_id, food_kind, food_name, food_price, food_count,food_image) 
VALUES (20, '700', '바질샤오마이딤섬', 11900, 50,'m2.png');
INSERT INTO food (food_id, food_kind, food_name, food_price, food_count,food_image) 
VALUES (21, '700', '닭가슴살교자만두', 14400, 50,'m3.png');


--관리자--
insert into manager(managerId, managerPasswd)
values('foodmaster@shop.com','123456');

--회원--
insert into member(id,passwd,name,email,address,tel) 
value ('hongkd','1111','홍길동','hongkd@aaa.com','인천시 남동구 정각로 29', '010-2222-1234');
insert into member(id,passwd,name,email,address,tel) 
value ('kingdora','1234','김개동','kingdora@dragon.com','경기도 구리시 아차산로 439', '010-3333-3333');
insert into member(id,passwd,name,email,address,tel) 
value ('aaaa','1234','박대로','aaaa@king.com','서울시 마포구 양화로6길 9', '010-1111-1111');


--임시 buy--
INSERT INTO buy (buy_id, buyer, food_id, food_name, buy_price, buy_count, food_image, 
buy_date, deliveryAddress)
values ( 2024041800001,'aaaa',1, '한우곱창전골',13800,1, 'ko1.png', '2024-04-18 12:40:18.0', '서울시 마포구 양화로6길 9');
INSERT INTO buy (buy_id, buyer, food_id, food_name, buy_price, buy_count, food_image, 
buy_date, deliveryAddress)
values ( 2024041800001,'aaaa',2, '전복미역국',13800,1, 'ko2.png', '2024-04-18 12:40:18.0', '서울시 마포구 양화로6길 9');
INSERT INTO buy (buy_id, buyer, food_id, food_name, buy_price, buy_count, food_image, 
buy_date, deliveryAddress)
values ( 2024041800001,'aaaa',3, '돼지김치찌개',5300,1, 'ko3.png', '2024-04-18 12:40:18.0', '서울시 마포구 양화로6길 9');






