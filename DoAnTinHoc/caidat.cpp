#include"Header.h"

// Hàm để in ra cây gia phả
void printFamilyTree(FamilyTree* root, int level = 0) {
    //nếu cây rỗng thì trả về
    if (root == nullptr) {
        return;
    }
    //duyệt biến i và xuất thông tin của các thành viên
    for (int i = 0; i < level; ++i) {
        cout << "  ";
    }
    cout << root->person->name <<root->person->relation<< " (" << root->person->birthYear << ")" << " (" << root->person->id << ")"<< endl;
    //tạo cây và tạo các biến con cho cây
    for (FamilyTree* child : root->children) {
        printFamilyTree(child, level + 1);
    }
}

// Hàm sửa thông tin thành viên
void editMember(FamilyTree* root, const int& id, const string& newName, string& newRelation, int newBirthYear) {
    FamilyTree* member = root->findID(id);//tìm thành viên bằng id
    if (member != nullptr) { 
        member->person->name = newName;//tạo tên mới cho thành viên
        member->person->relation = newRelation;//tạo mối quan hệ mới cho thành viên
        member->person->birthYear = newBirthYear;//tạo năm sinh mới cho thành viên
    }
    else {
        cout << "Member not found." << endl;
    }
}

// Hàm thêm thành viên vào gia phả
void addMember(FamilyTree* root, const int& id, Member* newMember) {
    FamilyTree* child = root->findID(id);//tìm thành viên cha bằng id
    if (child != nullptr) {
        FamilyTree* newMemberNode = new FamilyTree(newMember);//tạo nút mới cho thành viên của cây
        child->addChild(newMemberNode);//tạo nút con cho thành viên của cây
    }
    else {
        cout << "Parent not found." << endl;
    }
}
