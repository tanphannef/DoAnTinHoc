#include"Header.h"

int main() {
    // Tạo các thành viên gia đình
    Member* grandParent = new Member("phong","\t\tGrandpa", 1920, 1);
    Member* parent1 = new Member("phu","\t\tfather", 1950, 2);
    Member* parent2 = new Member("lam","\t\tfather", 1960, 4);
    Member* child1 = new Member("long","\tson", 1980, 6);
    Member* child2 = new Member("trinh","\tdaughter", 1985, 7);
    Member* child3 = new Member("trang","\tdaughter", 1988, 9);
    Member* child4 = new Member("linh","\tdaughter", 1983, 5);
    // Xây dựng cây gia phả
    FamilyTree* root = new FamilyTree(grandParent);
    FamilyTree* parent1Node = new FamilyTree(parent1);
    FamilyTree* parent2Node = new FamilyTree(parent2);
    FamilyTree* child1Node = new FamilyTree(child1);
    FamilyTree* child2Node = new FamilyTree(child2);
    FamilyTree* child3Node = new FamilyTree(child3);
    FamilyTree* child4Node = new FamilyTree(child4);

    root->addChild(parent1Node);
    root->addChild(parent2Node);
    parent1Node->addChild(child1Node);
    parent1Node->addChild(child2Node);
    parent2Node->addChild(child3Node);
    parent2Node->addChild(child4Node);

    //FamilyTree* root = nullptr;
    //FamilyTree* readRoot = readFamilyTreeFromFile("family_tree.txt");
    int a, namThayThe,idthaythe,id;
    string ten, tenThayThe, moiQuanHe;

    do
    {
        cout << "\n";
        cout << "Danh Sach Menu"<<"\n";
        cout << "0. Thoat" << "\n";
        cout << "1. xuat gia pha" << "\n";
        cout << "2. them" << "\n";
        cout << "3. xoa" << "\n";
        cout << "4. sua" << "\n";
        cout << "5. tim kiem" << "\n";
        cout << "Nhap so : ";
        cin >> a;
        switch (a)
        {
        case 0://thoat
            break;
        case 1://xuat
            cout << "Family Tree:" <<endl;
            printFamilyTree(root,0);
            break;
        case 2://them
            cout << "Adding new member:" << endl;
            cout << "Nhap id bo cua thanh vien moi:" << endl;
            cin >> id;
            cout << "Nhap ten thanh vien moi:" << endl;
            cin >> tenThayThe;
            cout << "Nhap moi quan he moi:" << endl;
            cin >> moiQuanHe;
            cout << "Nhap nam sinh thanh vien moi:" << endl;
            cin >> namThayThe;
            cout << "Nhap id thanh vien moi:" << endl;
            cin >> idthaythe;
            addMember(root, id, new Member(tenThayThe,moiQuanHe, namThayThe, idthaythe));
            printFamilyTree(root,0);
            break;
        case 3://xoa
            cout << "Deleting member:" << endl;
            cout << "id can xoa:" << endl;
            cin >> id;
            root->deleteMember(root,id);
            cout << endl;
            printFamilyTree(root,0);
            break;
        case 4://sua
            cout << "Editing member:" << endl;
            cout << " nhap id can thay the:" << endl;
            cin >> id;
            cout << "Ten thay the:" << endl;
            cin >> tenThayThe;
            cout << "Doi moi quan he:" << endl;
            cin >> moiQuanHe;
            cout << "Doi nam sinh:" << endl;
            cin >> namThayThe;
            editMember(root, id, tenThayThe, moiQuanHe, namThayThe);
            printFamilyTree(root,0);
            break;
        case 5://tim kiem
            cout << "Nhap id can tim : " << endl;
            cin >> idthaythe;
            if (root->findID(idthaythe) != nullptr) {
                cout << "Found member: " << root->findID(idthaythe)->person->name << root->findID(idthaythe)->person->relation << " (" << root->findID(idthaythe)->person->birthYear << ")"<<"\t"<< "(" << root->findID(idthaythe)->person->id << ")" << endl;
                root->findAndPrintSibling(idthaythe);
                if(idthaythe==1){
                    cout << "is root";
                }
            }
            else {
                cout << "Member not found." <<endl;
            }
            break;
        default:
            cout << "nhap lai: ";
            break;
        }

    } while (a!=0);

    return 0;
}
