#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
using namespace std;

//khởi tạo lớp có tên Member
class Member {
public:
    string name;//chuỗi chứa tên
    string relation;//chuỗi chứa mối quan hệ
    int birthYear;//số nguyên chứa năm sinh
    int id;//số nguyên chứa mã
    //khai báo hàm Member
    Member(string n, string m, int by, int id) : name(n), relation(m), birthYear(by), id(id) {}
};
//khởi tạo lớp có tên FamilyTree
class FamilyTree {
public:
    Member* person;//khai báo kiểu dữ liệu Member có con trỏ tới person
    vector<FamilyTree*> children;//khai báo vector children

    FamilyTree(Member* p) : person(p) {}

    //hàm thêm con vào nút
    void addChild(FamilyTree* child) {
        children.push_back(child);
    }

    //tìm thành viên bằng id
    FamilyTree* findID(const int& id) {
        //kiểm tra id cân tìm có phải là id của đối tượng đực truyền vào hay không nếu đúng hàm trả về chính đối tượng đó
        if (person->id == id) {
            return this;
        }
        //duyệt qua danh sách thành viên con
        for (FamilyTree* child : children) {
            FamilyTree* result = child->findID(id);
            if (result != nullptr) {
                return result;
            }
        }
        return nullptr;
    }

    ~FamilyTree() {
        for (FamilyTree* child : children) {//duyệt qua các con của thành viên
            delete child;//xóa dữ liệu nút con
        }
    }
    // Hàm xóa thành viên từ cây
    void deleteMember(FamilyTree*root, const int& id) {
        //gọi hàm tìm kiếm thành viên bằng id
        FamilyTree* member = findID(id);
        if (member) {//hàm kiểm tra member có rỗng hay không nếu không thì gọi hàm removeMembers
            removeMember(member,id);
        }
        else {
            cout << "Member not found";
        }
    }

    //hàm kiểm tra xóa thành viên
    bool removeMember(FamilyTree*member, const int& id) {
        //tìm thành viên cần xóa trong danh sách con
        auto p = find(children.begin(), children.end(), member);
        //nếu thành viên đc tìm thấy thì xóa khỏi danh sách
        if (p != children.end()) {
            children.erase(p);//xóa thành viên
            delete member;
        }
        //duyệt qua danh sách con của tất cả thành viên
        for (auto p = children.begin(); p != children.end(); ++p) {
            //nếu tìm thấy thì gọi hàm removeMembers để xóa thành viên khỏi danh sách
            if ((*p)->person->id == id && (*p)->children.empty()) {
                delete* p;
                children.erase(p);
                return true;
            }
            else {
                if ((*p)->removeMember(member,id)) {
                    return true;
                }
            }
        }
        return false;
    }

    //hàm tìm thành viên và xuất anh chị em
    void findAndPrintSibling(const int& id) {
        //gọi hàm tìm kiếm thành viên bằng id
        FamilyTree* member = findID(id);
        if (member) {//hàm kiểm tra member có rỗng hay không nếu không thì gọi hàm printMembers
            printMembers(member);
        }
        else {
            cout << "Member not found";
        }
    }

    //hàm xuất những người xung quanh
    void printMembers(FamilyTree* member) {
        //gọi hàm getParent để trỏ đến nút cha
        FamilyTree* parent = getParent(this, member);
        if (parent) {//kiểm tra parent có rỗng hay không
            //duyệt qua các thành viên con
            for (FamilyTree* sibling : parent->children) {
                if (sibling != member) {// kiểm tra xem sibling có phải là member hay không nếu sibling không phải là member thì hàm sẽ in ra tên của sibling.
                    cout << "anh/chi em cua " << member->person->name << ":" << sibling->person->name << endl;
                }
            }
        }
        else {
            cout << "(" << member->person->name << ")" << "la nut goc, khong co anh chi em" << endl;
        }
    }

    //lấy cha của 1 nút gốc trong cây
    FamilyTree* getParent(FamilyTree* root, FamilyTree* child) {
        //duyệt qua các thành viên con
        for (FamilyTree* sibling : root->children) {
            //duyệt qua các thành viên của nút con của nút con hiện tại
            for (FamilyTree* grandchild : sibling->children) {
                if (grandchild == child) {//kiểm tra xem nút con hiện tại có phải là child hay không nếu có thì hàm trả về nút con hiện tại.
                    return sibling;
                }
            }
            FamilyTree* result = getParent(sibling, child);//gọi hàm getParent
            if (result) {//kiểm tra xem hàm getParent có trả về một giá trị khác null hay không nếu có thì hàm trả về giá trị đó.
                return result;
            }
        }
        return nullptr;
    }
};

//khai báo hàm
void printFamilyTree(FamilyTree* root, int level);
void editMember(FamilyTree* root, const int& id, const string& newName, string& relation, int newBirthYear);
void addMember(FamilyTree* root, const int& id, Member* newMember);
void saveMemberToFile(ofstream& file, FamilyTree* node, int level);
void saveFamilyTreeToFile(FamilyTree* root, const string& filename);
pair<string, int> parseMemberInfo(const string& line);
FamilyTree* readFamilyTreeFromFile(const string& filename);
