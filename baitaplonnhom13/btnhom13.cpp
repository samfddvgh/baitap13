#include <iostream>
#include <string>
using namespace std;

struct SeatNode {
    int seatNumber;
    bool isBooked;
    string classType;
    long long tien;  
    string idCard;    
    string ten;
    string gioitinh;
    int tuoikh;
    string idCardNumber; 
    SeatNode* left;
    SeatNode* right;

    SeatNode(int seatNum, const string& type, long long seatTien)  
        : seatNumber(seatNum), isBooked(false), classType(type), tien(seatTien), tuoikh(0), left(NULL), right(NULL) {}
};

long long tinhgia(long long giabth, int tuoi) {
    if (tuoi >= 12) {
        return giabth;
    } else if (tuoi >= 2) {
        return giabth * 0.75; 
    } else {
        return 100000;  
    }
}

SeatNode* insertSeat(SeatNode* node, int seatNumber, const string& classType, long long tien) {
    if (node == NULL) {
        return new SeatNode(seatNumber, classType, tien);
    }
    if (seatNumber < node->seatNumber) {
        node->left = insertSeat(node->left, seatNumber, classType, tien);
    } else if (seatNumber > node->seatNumber) {
        node->right = insertSeat(node->right, seatNumber, classType, tien);
    }
    return node;
}

SeatNode* findSeat(SeatNode* node, int seatNumber) {
    if (node == NULL || node->seatNumber == seatNumber) {
        return node;
    }
    if (seatNumber < node->seatNumber) {
        return findSeat(node->left, seatNumber);
    }
    return findSeat(node->right, seatNumber);
}

void bookSeat(SeatNode* root, int seatNumber, const string& idCard, const string& idCardNumber, const string& ten, const string& gioitinh, int tuoi) {
    SeatNode* seat = findSeat(root, seatNumber);
    if (seat == NULL) {
        cout << "Khong tim thay ghe so " << seatNumber << ".\n";
    } else if (seat->isBooked) {
        cout << "Ghe so " << seatNumber << " da duoc dat truoc.\n";
    } else if (idCard.empty() || (idCard != "CCCD" && idCard != "HoChieu" && idCard != "GiayKhaiSinh")) {
        cout << "Khong the dat ve vi thieu giay to hop le (CCCD, Hochieu, Giaykhaisinh).\n";
    } else {
        seat->isBooked = true;
        seat->idCard = idCard;
        seat->idCardNumber = idCardNumber;
        seat->ten = ten;
        seat->gioitinh = gioitinh;
        seat->tuoikh = tuoi;
        long long giacuoi = tinhgia(seat->tien, tuoi);
        cout << "Da dat thanh cong ghe so " << seatNumber << " (Hang: " << seat->classType << ", Gia: " << giacuoi
             << ") cho " << ten << " (" << gioitinh << ", Tuoi: " << tuoi << ").\n";
    }
}
