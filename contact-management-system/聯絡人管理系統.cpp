#include <iostream>
#include <string>
using namespace std;

#define maxPersons 1000 // 最大上限聯絡人

// 聯絡人
struct Person
{
    string name; // 姓名
    short sex = 0; // 性別 女 0 男 1　其他 2
    short age = 18; // 年齡
    string phone; // 電話號碼
};

// 通訊綠
struct ContactBook
{
    Person persons[maxPersons]; // Person 陣列
    int currentPerson = 0; // 當前聯絡人數量（初始值為 0）
};

// 顯示選單
void showMenu()
{
    cout << "*****************************" << endl;
    cout << "*****   1. 新增聯絡人   *****" << endl;
    cout << "*****   2. 顯示聯絡人   *****" << endl;
    cout << "*****   3. 刪除聯絡人   *****" << endl;
    cout << "*****   4. 查詢聯絡人   *****" << endl;
    cout << "*****   5. 編輯聯絡人   *****" << endl;
    cout << "*****   6. 清空聯絡人   *****" << endl;
    cout << "*****   0. 退出系統　   *****" << endl;
    cout << "*****************************" << endl;

    cout << endl << "請輸入編號（0 ~ 6）使用功能：" << endl;
}

// 新增聯絡人
void addPerson(ContactBook* contactBook)
{
    int currentPerson = contactBook->currentPerson; // 當前聯絡人數量

    // 檢查是否超出上限值
    if (currentPerson == maxPersons) // 如果當前聯絡人數量等於上限值時
    {
        cout << "聯絡人以超出上限 " << maxPersons << endl;
        return;
    }

    // 姓名
    cout << "請輸入聯絡人姓名：" << endl;
    cin >> contactBook->persons[currentPerson].name;

    // 性別
    int inputSex; // 用戶輸入的性別

    cout << "請輸入性別（女 = 0, 男 = 1, 其他 = 2）：" << endl;

    while (true)
    {
        cin >> inputSex;

        if (inputSex == 0 || inputSex == 1 || inputSex == 2)
        {
            contactBook->persons[currentPerson].sex = inputSex;
            break;
        }

        cout << "請輸入正確的性別！" << endl;
    }

    // 年齡
    int inputAge; // 用戶輸入的年齡

    cout << "請輸入年齡（0 ~ 150）：" << endl;

    while (true)
    {
        cin >> inputAge;

        if (inputAge >= 0 && inputAge <= 150)
        {
            contactBook->persons[currentPerson].age = inputAge;
            break;
        }

        cout << "請輸入正確的年齡有效範圍 0 ~ 150！" << endl;
    }

    // 電話號碼
    cout << "請輸入電話號碼：" << endl;
    cin >> contactBook->persons[currentPerson].phone;

    // 完成前操作
    cout << endl << "新增聯絡人 " << contactBook->persons[currentPerson].name << " 成功！" << endl;

    contactBook->currentPerson++; // 聯絡人數量 +1

    return;
}

// 顯示聯絡人
void showPersons(ContactBook* contactBook)
{
    int currentPerson = contactBook->currentPerson;

    if (currentPerson == 0)
    {
        cout << "當前沒有聯絡人。" << endl;
        return;
    }

    for (int i = 0; i < currentPerson; i++)
    {
        cout << "姓名：" << contactBook->persons[i].name
             << "\t性別：" << (contactBook->persons[i].sex == 0 ? "女" :
                              contactBook->persons[i].sex == 1 ? "男" : "其他")
             << "\t年齡：" << contactBook->persons[i].age
             << "\t電話號碼：" << contactBook->persons[i].phone << endl;
    }

    cout << endl;
    return;
}

// 查找聯絡人，存在返回索引值，否則返回 -1
int isExist(ContactBook* contactBook, string name)
{
    int currentPerson = contactBook->currentPerson; // 聯絡人數量

    if (currentPerson == 0) return -1; // 如果聯絡人數量為 0 則直接返回 -1

    for (int i = 0; i < currentPerson; i++)
    {
        if (contactBook->persons[i].name == name) // 如果 name 相同
        {
            return i; // 返回索引值
        }
    }

    return -1; // 遍歷結束，找不到聯絡人
}

// 刪除聯絡人
void deletePerson(ContactBook* contactBook)
{

    cout << "請輸入要刪除的聯絡人姓名：" << endl;

    string inputName;
    cin >> inputName;

    int personIndex = isExist(contactBook, inputName);

    if (personIndex == -1)
    {
        cout << endl << "找不到要刪除的聯絡人。" << endl;
        return;
    }

    // 從找到的索引值開始，循環將後一個值往前覆蓋
    for (int i = personIndex; i < contactBook->currentPerson; i++)
    {
        contactBook->persons[i] = contactBook->persons[i + 1];
    }

    contactBook->currentPerson--; // 聯絡人數量 -1

    cout << endl << "刪除聯絡人 " << inputName << " 成功！" << endl;
}

// 查詢聯絡人
void fintPerson(ContactBook* contactBook)
{
    cout << "請輸入要查詢的聯絡人姓名：" << endl;

    string inputName;
    cin >> inputName;

    int personIndex = isExist(contactBook, inputName);

    if (personIndex == -1)
    {
        cout << endl << "找不到要查詢的聯絡人。" << endl;
        return;
    }

    cout << endl
         << "姓名：" << contactBook->persons[personIndex].name
         << "\t性別：" << (contactBook->persons[personIndex].sex == 0 ? "女" :
                          contactBook->persons[personIndex].sex == 1 ? "男" : "其他")
         << "\t年齡：" << contactBook->persons[personIndex].age
         << "\t電話號碼：" << contactBook->persons[personIndex].phone << endl;

    return;
}

// 編輯聯絡人
void editPerson(ContactBook* contactBook)
{
    cout << "請輸入要編輯的聯絡人姓名：" << endl;

    string inputName;
    cin >> inputName;

    int personIndex = isExist(contactBook, inputName);

    if (personIndex == -1)
    {
        cout << endl << "找不到要編輯的聯絡人。" << endl;
        return;
    }
    
    // 姓名
    cout << "請輸入聯絡人姓名：" << endl;
    cin >> contactBook->persons[personIndex].name;

    // 性別
    int inputSex; // 用戶輸入的性別

    cout << "請輸入性別（女 = 0, 男 = 1, 其他 = 2）：" << endl;

    while (true)
    {
        cin >> inputSex;

        if (inputSex == 0 || inputSex == 1 || inputSex == 2)
        {
            contactBook->persons[personIndex].sex = inputSex;
            break;
        }

        cout << "請輸入正確的性別！" << endl;
    }

    // 年齡
    int inputAge; // 用戶輸入的年齡

    cout << "請輸入年齡（0 ~ 150）：" << endl;

    while (true)
    {
        cin >> inputAge;

        if (inputAge >= 0 && inputAge <= 150)
        {
            contactBook->persons[personIndex].age = inputAge;
            break;
        }

        cout << "請輸入正確的年齡有效範圍 0 ~ 150！" << endl;
    }

    // 電話號碼
    cout << "請輸入電話號碼：" << endl;
    cin >> contactBook->persons[personIndex].phone;

    // 完成前操作
    cout << endl << "編輯聯絡人 " << contactBook->persons[personIndex].name << " 成功！" << endl;

    return;
}

// 清空聯絡人
void clearAllPerson(ContactBook* contactBook)
{
    contactBook->currentPerson = 0; // 只需要將當前聯絡人數量設為 0 即可

    cout << endl << "清空聯絡人成功！" << endl;

    return;
}

int main()
{
    system("title 聯絡人管理系統");

    ContactBook contactBook; // 通訊綠
    int select; // 用戶輸入

    while (true)
    {
        // 顯示選單
        showMenu();

        // 用戶輸入賦值
        cin >> select;
        
        system("cls");

        switch (select)
        {
            case 1 : // 新增聯絡人
                addPerson(&contactBook);
                break;

            case 2 : // 顯示聯絡人
                showPersons(&contactBook);
                break;

            case 3 : // 刪除聯絡人
                deletePerson(&contactBook);
                break;

            case 4 : // 查詢聯絡人
                fintPerson(&contactBook);
                break;

            case 5 : // 編輯聯絡人
                editPerson(&contactBook);
                break;

            case 6 : // 清空聯絡人
                clearAllPerson(&contactBook);
                break;

            case 0 : // 退出系統
                cout << "歡迎再次使用！" << endl;
                system("pause");
                return 0;

            default : // 其他
                cout << "請輸入正確的選項！" << endl;
        }

        system("pause");
        system("cls");
    }
}