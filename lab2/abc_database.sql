-- Tạo Database
CREATE DATABASE ABCBank;
GO

USE ABCBank;
GO

-- Bảng chi nhánh
CREATE TABLE BRANCH (
    Name VARCHAR(100) PRIMARY KEY,
    AddressNo VARCHAR(20),
    Street VARCHAR(100),
    District VARCHAR(100),
    City VARCHAR(100),
    Region VARCHAR(100),
    Email VARCHAR(100),
    TotalEmployees INT DEFAULT 0,   -- tổng số nhân viên
    MngCode INT NULL                -- khóa ngoại quản lý
);

-- Bảng điện thoại chi nhánh
CREATE TABLE BRANCHPHONE (
    BraName VARCHAR(100),
    Phone VARCHAR(20),
    PRIMARY KEY (BraName, Phone),
    FOREIGN KEY (BraName) REFERENCES BRANCH(Name)
);

-- Bảng fax chi nhánh
CREATE TABLE BRANCHFAX (
    BraName VARCHAR(100),
    Fax VARCHAR(20),
    PRIMARY KEY (BraName, Fax),
    FOREIGN KEY (BraName) REFERENCES BRANCH(Name)
);

-- Bảng nhân viên
CREATE TABLE EMPLOYEE (
    Code INT PRIMARY KEY,
    FName VARCHAR(50),
    LName VARCHAR(50),
    AddressNo VARCHAR(20),
    Street VARCHAR(100),
    District VARCHAR(100),
    City VARCHAR(100),
    DOB DATE,
    Email VARCHAR(100),
    BraName VARCHAR(100) NOT NULL,
    FOREIGN KEY (BraName) REFERENCES BRANCH(Name)
);

-- Bảng điện thoại nhân viên
CREATE TABLE EMPLOYEEPHONE (
    EmpCode INT,
    Phone VARCHAR(20),
    PRIMARY KEY (EmpCode, Phone),
    FOREIGN KEY (EmpCode) REFERENCES EMPLOYEE(Code)
);

-- Bảng khách hàng
CREATE TABLE CUSTOMER (
    Code INT PRIMARY KEY,
    FName VARCHAR(50),
    LName VARCHAR(50),
    OfficeAddress VARCHAR(200),
    HomeAddress VARCHAR(200),
    Email VARCHAR(100),
    EmpCode INT NOT NULL,
    FOREIGN KEY (EmpCode) REFERENCES EMPLOYEE(Code)
);

-- Bảng điện thoại khách hàng
CREATE TABLE CUSTOMERPHONE (
    CusCode INT,
    Phone VARCHAR(20),
    PRIMARY KEY (CusCode, Phone),
    FOREIGN KEY (CusCode) REFERENCES CUSTOMER(Code)
);

-- Bảng tài khoản
CREATE TABLE ACCOUNT (
    Number INT PRIMARY KEY,
    CusCode INT NOT NULL,
    FOREIGN KEY (CusCode) REFERENCES CUSTOMER(Code)
);

-- Bảng tài khoản tiết kiệm
CREATE TABLE SAVINGACCOUNT (
    AccNumber INT PRIMARY KEY,
    Balance DECIMAL(18,2),
    InterestRate DECIMAL(5,2),
    OpenedDate DATE,
    FOREIGN KEY (AccNumber) REFERENCES ACCOUNT(Number)
);

-- Bảng tài khoản vãng lai
CREATE TABLE CHECKINGACCOUNT (
    AccNumber INT PRIMARY KEY,
    Balance DECIMAL(18,2),
    OpenedDate DATE,
    FOREIGN KEY (AccNumber) REFERENCES ACCOUNT(Number)
);

-- Bảng khoản vay
CREATE TABLE LOAN (
    AccNumber INT PRIMARY KEY,
    BalanceDue DECIMAL(18,2),
    InterestRate DECIMAL(5,2),
    TakenDate DATE,
    FOREIGN KEY (AccNumber) REFERENCES ACCOUNT(Number)
);

-- Thêm ràng buộc quản lý chi nhánh
ALTER TABLE BRANCH
ADD CONSTRAINT FK_Branch_Manager FOREIGN KEY (MngCode) REFERENCES EMPLOYEE(Code);


CREATE TRIGGER trg_UpdateBranchTotalEmployees
ON EMPLOYEE
AFTER INSERT, DELETE
AS
BEGIN
    -- Khi thêm nhân viên
    UPDATE BRANCH
    SET TotalEmployees = (
        SELECT COUNT(*) FROM EMPLOYEE WHERE EMPLOYEE.BraName = BRANCH.Name
    )
    WHERE Name IN (
        SELECT DISTINCT BraName FROM INSERTED
        UNION
        SELECT DISTINCT BraName FROM DELETED
    );
END;
