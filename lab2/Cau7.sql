USE ABCBank;
GO
/* 
	a. You are required to insert valid and meaningful data 
	into the database.Each table has at least 4 rows 
*/

-- 1. Branches
INSERT INTO BRANCH (Name, AddressNo, Street, District, City, Region, Email, TotalEmployees, MngCode)
VALUES 
('Hanoi_Main', '101', 'Kim Ma', 'Ba Dinh', 'Hanoi', 'North', 'hanoi_main@abcbank.com', 0, NULL),
('HCM_Center', '88', 'Le Loi', 'Quan 1', 'HCM', 'South', 'hcm_center@abcbank.com', 0, NULL),
('Danang_Office', '55', 'Nguyen Van Linh', 'Hai Chau', 'Da Nang', 'Central', 'danang_office@abcbank.com', 0, NULL),
('Cantho_Branch', '22', '30/4', 'Ninh Kieu', 'Can Tho', 'Mekong', 'cantho_branch@abcbank.com', 0, NULL);

-- 2. BranchPhone Table
INSERT INTO BRANCHPHONE VALUES ('Hanoi_Main', '024-1111111');
INSERT INTO BRANCHPHONE VALUES ('Hanoi_Main', '024-2222222');
INSERT INTO BRANCHPHONE VALUES ('HCM_Center', '028-3333333');
INSERT INTO BRANCHPHONE VALUES ('Danang_Office', '0236-4444444');
INSERT INTO BRANCHPHONE VALUES ('Cantho_Branch', '0292-5555555');

-- 3. BranchFax Table
INSERT INTO BRANCHFAX VALUES ('Hanoi_Main', '024-9999999');
INSERT INTO BRANCHFAX VALUES ('HCM_Center', '028-8888888');
INSERT INTO BRANCHFAX VALUES ('Danang_Office', '0236-7777777');
INSERT INTO BRANCHFAX VALUES ('Cantho_Branch', '0292-6666666');

-- 4. Employees
INSERT INTO EMPLOYEE (Code, FName, LName, AddressNo, Street, District, City, DOB, Email, BraName)
VALUES
(1, 'Nguyen', 'An', '12', 'Tran Phu', 'Ha Dong', 'Hanoi', '1985-04-12', 'an.nguyen@abcbank.com', 'Hanoi_Main'),
(2, 'Tran', 'Binh', '45', 'Nguyen Trai', 'Thanh Xuan', 'Hanoi', '1990-08-22', 'binh.tran@abcbank.com', 'Hanoi_Main'),
(3, 'Le', 'Hoa', '20', 'Pasteur', 'Quan 3', 'HCM', '1987-11-05', 'hoa.le@abcbank.com', 'HCM_Center'),
(4, 'Pham', 'Cuong', '55', 'Vo Thi Sau', 'Quan 1', 'HCM', '1992-02-15', 'cuong.pham@abcbank.com', 'HCM_Center'),
(5, 'Do', 'Thang', '78', 'Le Duan', 'Hai Chau', 'Da Nang', '1980-03-18', 'thang.do@abcbank.com', 'Danang_Office'),
(6, 'Nguyen', 'Huong', '33', 'Hoang Dieu', 'Hai Chau', 'Da Nang', '1995-12-07', 'huong.nguyen@abcbank.com', 'Danang_Office'),
(7, 'Vo', 'Khanh', '9', 'Nguyen Trai', 'Ninh Kieu', 'Can Tho', '1983-06-20', 'khanh.vo@abcbank.com', 'Cantho_Branch'),
(8, 'Pham', 'Ly', '100', 'Ly Tu Trong', 'Ninh Kieu', 'Can Tho', '1991-09-10', 'ly.pham@abcbank.com', 'Cantho_Branch'),
(9, 'Nguyen', 'Vinh', '102', 'Hoa Hung', 'Quan 10', 'HCM', '2010-03-10', 'ly.pham@abcbank.com', 'Cantho_Branch');

-- 5. EmployeePhone Table
INSERT INTO EMPLOYEEPHONE VALUES (1, '0912000001');
INSERT INTO EMPLOYEEPHONE VALUES (2, '0912000002');
INSERT INTO EMPLOYEEPHONE VALUES (3, '0933000003');
INSERT INTO EMPLOYEEPHONE VALUES (4, '0933000004');
INSERT INTO EMPLOYEEPHONE VALUES (5, '0905000005');
INSERT INTO EMPLOYEEPHONE VALUES (6, '0905000006');
INSERT INTO EMPLOYEEPHONE VALUES (7, '0917000007');
INSERT INTO EMPLOYEEPHONE VALUES (8, '0917000008');


-- 6. Customer Table
INSERT INTO CUSTOMER (Code, FName, LName, OfficeAddress, HomeAddress, Email, EmpCode)
VALUES
(1001, 'Hoang', 'Minh', 'FPT Tower, Hanoi', '123 Hoang Quoc Viet, Hanoi', 'minh.hoang@gmail.com', 1),
(1002, 'Vu', 'Lan', 'Viettel HQ, Hanoi', '45 Nguyen Chi Thanh, Hanoi', 'lan.vu@yahoo.com', 2),
(1003, 'Nguyen', 'Phuong', 'Vincom, HCM', '12 Nguyen Hue, HCM', 'phuong.nguyen@gmail.com', 3),
(1004, 'Tran', 'Son', 'Techcombank Tower, HCM', '88 Cach Mang Thang 8, HCM', 'son.tran@outlook.com', 4),
(1005, 'Le', 'Trang', 'Da Nang Software Park', '99 Hoang Dieu, Da Nang', 'trang.le@gmail.com', 5),
(1006, 'Bui', 'Hai', 'Mobifone Da Nang', '12 Ong Ich Khiem, Da Nang', 'hai.bui@yahoo.com', 6),
(1007, 'Pham', 'Quyen', 'Can Tho University', '30/4 Street, Can Tho', 'quyen.pham@gmail.com', 7),
(1008, 'Nguyen', 'Duc', 'VNPT Can Tho', '77 Hung Vuong, Can Tho', 'duc.nguyen@outlook.com', 8);


-- 7. CustomerPhone Table
INSERT INTO CUSTOMERPHONE VALUES (1001, '0987000001');
INSERT INTO CUSTOMERPHONE VALUES (1002, '0987000002');
INSERT INTO CUSTOMERPHONE VALUES (1003, '0978000003');
INSERT INTO CUSTOMERPHONE VALUES (1004, '0978000004');
INSERT INTO CUSTOMERPHONE VALUES (1005, '0969000005');
INSERT INTO CUSTOMERPHONE VALUES (1006, '0969000006');
INSERT INTO CUSTOMERPHONE VALUES (1007, '0958000007');
INSERT INTO CUSTOMERPHONE VALUES (1008, '0958000008');

-- 8. Account Table
INSERT INTO ACCOUNT VALUES (20001, 1001);
INSERT INTO ACCOUNT VALUES (20002, 1002);
INSERT INTO ACCOUNT VALUES (20003, 1003);
INSERT INTO ACCOUNT VALUES (20004, 1004);
INSERT INTO ACCOUNT VALUES (20005, 1005);
INSERT INTO ACCOUNT VALUES (20006, 1006);
INSERT INTO ACCOUNT VALUES (20007, 1007);
INSERT INTO ACCOUNT VALUES (20008, 1008);
INSERT INTO ACCOUNT VALUES (20009, 1001); 
INSERT INTO ACCOUNT VALUES (20010, 1003); 



-- 9. SavingAccount Table
INSERT INTO SAVINGACCOUNT VALUES (20001, 50000000, 3.5, '2022-01-15');
INSERT INTO SAVINGACCOUNT VALUES (20003, 120000000, 4.0, '2021-11-01');
INSERT INTO SAVINGACCOUNT VALUES (20005, 70000000, 3.2, '2022-05-22');
INSERT INTO SAVINGACCOUNT VALUES (20007, 30000000, 3.8, '2023-03-10');
INSERT INTO SAVINGACCOUNT VALUES (20009, 36360000, 3.6, '2023-06-03');

-- 10. Checking accounts Table
INSERT INTO CHECKINGACCOUNT VALUES (20002, 15000000, '2023-05-10');
INSERT INTO CHECKINGACCOUNT VALUES (20006, 10000000, '2024-01-15');
INSERT INTO CHECKINGACCOUNT VALUES (20009, 8000000, '2024-02-20');
INSERT INTO CHECKINGACCOUNT VALUES (20005, 3636000, '2024-06-03');


-- 11. Loans Table
INSERT INTO LOAN VALUES (20004, 200000000, 8.5, '2023-06-01');
INSERT INTO LOAN VALUES (20008, 100000000, 7.2, '2022-09-15');
INSERT INTO LOAN VALUES (20010, 50000000, 6.8, '2024-04-01');
INSERT INTO LOAN VALUES (20002, 69690000, 6.9, '2024-09-06');


-- 12. Cập nhật Manager cho Branch
------------------------
UPDATE BRANCH SET MngCode = 1 WHERE Name = 'Hanoi_Main';
UPDATE BRANCH SET MngCode = 3 WHERE Name = 'HCM_Center';
UPDATE BRANCH SET MngCode = 5 WHERE Name = 'Danang_Office';
UPDATE BRANCH SET MngCode = 7 WHERE Name = 'Cantho_Branch';
-------------------------------------------------------------------------------


-- b. Change last name of an employee whose code is “8” to “Brown”.
UPDATE EMPLOYEE SET LName = 'Brown' WHERE Code = 8

-- c. Delete the employee having code “N1080”. Explain what will happen to the customers who are severed by this employee.
DELETE EMPLOYEE WHERE Code = 8
/* 
 Vì có ràng buộc toàn vẹn, liên kết khoá ngoại thuộc tính ECode trong bảng EMPPhone và bảng Customer nên không thể xoá được
 */

 -- d. Retrieve all account numbers of a customer whose name is Hoang Minh.
 SELECT A.Number as AccountNumber, C.Code, C.FName + ' ' + C.LName as FullName
 FROM CUSTOMER C
 JOIN ACCOUNT A ON C.Code = A.CusCode
 WHERE C.FName + ' ' + C.LName = N'Hoang Minh'

-- e. Find all employees who have their birthdays in March 2010.
 SELECT *
 FROM EMPLOYEE
 WHERE YEAR(DOB) = 2010 AND MONTH(DOB) = 3

 -- f. Retrieve the total balance of all saving accounts owned by a customer named “Hoang Minh” (Supposing that he has many saving accounts)
SELECT C.Code, C.FName + ' ' + C.LName as FullName, C.Email, SUM(Balance) as TotalBalance
FROM CUSTOMER C
JOIN ACCOUNT A ON C.Code = A.CusCode
JOIN SAVINGACCOUNT S ON S.AccNumber = A.Number
WHERE C.FName + ' ' + C.LName = N'Hoang Minh'
GROUP BY C.Code, C.FName + ' ' + C.LName, C.Email