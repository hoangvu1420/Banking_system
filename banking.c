#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct day
{
    int year, month, day;
} day;

typedef struct transaction
{
    day trans_day;
    int trans_type;
    double trans_amount;
    double current_balance;
} trans;

typedef struct customer
{
    char soTK[11];
    char MK[7];
    day ngay_taoTK;
    char ten_chuTK[20];
    day ngay_sinh_chuTK;
    char cmnd[10];
    double soDu;
    int flag;
    trans BD_soDu[10];
    int soBD;
} cus;

typedef struct admin
{
    char tenTK[9];
    char mk[7];
    day ngay_taoTK;
    char tenAd[20];
} ad;

int input_cus(cus a[])
{
    int n = 0;
    FILE *f = fopen("banking.txt", "r");
    if (feof(f))
        printf("\nERROR");
    else
    {
        fseek(f, 0, SEEK_SET);
        while (1)
        {
            char c = fgetc(f);
            if (c == EOF)
                break;
            else if (c == '=')
            {
                fscanf(f, "%[^|]", &a[n].soTK);
                fscanf(f, "|%[^|]", &a[n].MK);
                fscanf(f, "|%d/%d/%d", &a[n].ngay_taoTK.day, &a[n].ngay_taoTK.month, &a[n].ngay_taoTK.year);
                fscanf(f, "|%[^|]", &a[n].ten_chuTK);
                fscanf(f, "|%d/%d/%d", &a[n].ngay_sinh_chuTK.day, &a[n].ngay_sinh_chuTK.month, &a[n].ngay_sinh_chuTK.year);
                fscanf(f, "|%[^|]", &a[n].cmnd);
                fscanf(f, "|%d|", &a[n].flag);
                int n1 = 0;
                while (1)
                {
                    char c1 = fgetc(f);
                    if (c1 == '\n')
                        break;
                    else if (c1 == '*')
                    {
                        fscanf(f, "%d/%d/%d-", &a[n].BD_soDu[n1].trans_day.day, &a[n].BD_soDu[n1].trans_day.month, &a[n].BD_soDu[n1].trans_day.year);
                        fscanf(f, "%d-", &a[n].BD_soDu[n1].trans_type);
                        fscanf(f, "%lf-", &a[n].BD_soDu[n1].trans_amount);
                        fscanf(f, "%lf-", &a[n].BD_soDu[n1].current_balance);

                        // printf("%d/%d/%d\n", a[n].BD_soDu[n1].trans_day.day, a[n].BD_soDu->trans_day.month, a[n].BD_soDu->trans_day.year);
                        n1++;
                    }
                }
                a[n].soDu = a[n].BD_soDu[n1 - 1].current_balance;
                a[n].soBD = n1;
                n++;
            }
        }
    }
    fclose(f);
    return n;
}

int input_ad(ad adm[])
{
    int n = 0;
    FILE *f = fopen("banking.txt", "r");
    if (feof(f))
        printf("\nERROR");
    else
    {
        fseek(f, 0, SEEK_SET);
        while (1)
        {
            char c = fgetc(f);
            if (c == EOF)
                break;
            else if (c == '#')
            {
                fscanf(f, "%[^|]", &adm[n].tenTK);
                fscanf(f, "|%[^|]", &adm[n].mk);
                fscanf(f, "|%d/%d/%d", &adm[n].ngay_taoTK.day, &adm[n].ngay_taoTK.month, &adm[n].ngay_taoTK.year);
                fscanf(f, "|%[^\n]", &adm[n].tenAd);
                n++;
            }
            else if (c == '\n')
                continue;
        }
    }
    fclose(f);
    return n;
}

int login(cus a[], int n)
{
    char s[11], mk[7];
    printf("\n----Dang nhap tai khoan----");
    printf("\nNhap so TK: ");
    scanf("%s", &s);
    fflush(stdin);
    int x = -1;
    for (int i = 0; i < n; i++)
    {
        if (strcmp(a[i].soTK, s) == 0)
            x = i;
    }
    while (x == -1)
    {
        printf("So TK khong ton tai, hay nhap lai: ");
        scanf("%s", &s);
        fflush(stdin);
        for (int i = 0; i < n; i++)
        {
            if (strcmp(a[i].soTK, s) == 0)
                x = i;
        }
    }
    if (a[x].flag == 1)
    {
        printf("\n");
        printf("----- Tai khoan hien da bi khoa -----");
        return -1;
    }
    else
    {
        printf("Nhap mat khau: ");
        scanf("%s", &mk);
        int lan_nhap = 5;
        while (strcmp(mk, a[x].MK) != 0)
        {
            printf("Mat khau khong dung, hay thu lai (con %d lan nhap): ", lan_nhap);
            scanf("%s", &mk);
            lan_nhap--;
            if (lan_nhap == 0)
            {
                printf("Ban da nhap sai mat khau qua nhieu lan, tai khoan da bi khoa");
                a[x].flag = 1;
                return -1;
            }
        }
    }
    printf("\n<<< Dang nhap thanh cong >>>");
    printf("\nXin chao %s", a[x].ten_chuTK);
    return x;
}

int GetRandom(int min, int max) // Hàm lấy random các số từ min đến max
{
    return min + (int)(rand() * (max - min + 1.0) / (1.0 + RAND_MAX));
}

day specify_today()
{
    day today;
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    today.day = tm.tm_mday;
    today.month = tm.tm_mon + 1;
    today.year = tm.tm_year + 1900;
    return today;
}

void createAccount(cus a[], int *n)
{
    char news[11], mk[7];
    printf("\n----- Tao tai khoan -----");
    srand((unsigned int)time(NULL));
    int sw, sw1 = 0;
    do
    {
        do
        {
            char s[8];
            strcpy(news, "110");
            sw1 = 0;
            int r = GetRandom(1000000, 9999999);
            itoa(r, s, 10);
            strcat(news, s);
            for (int i = 0; i < *n; i++)
            {
                if (strcmp(a[i].soTK, news) == 0)
                {
                    sw1 = 1;
                    printf("\nerror");
                }
            }
        } while (sw1 == 1);
        printf("\nSSo tai khoan de xuat: %s", news);
        printf("\n1 - Chap nhan");
        printf("\n2 - Doi so tai khoan khac");
        printf("\n>>> ");
        scanf("%d", &sw);
    } while (sw == 2);
    strcpy(a[*n].soTK, news);
    printf("Nhap mat khau: ");
    scanf("%s", &a[*n].MK);
    while (strlen(a[*n].MK) != 6)
    {
        printf("Xac nhan lai mat khau: ");
        scanf("%s", &a[*n].MK);
    }
    fflush(stdin);
    printf("Nhap ten chu tai khoan TK: ");
    scanf("%[^\n]", &a[*n].ten_chuTK);
    a[*n].ngay_taoTK = specify_today();
    printf("Nhap ngay sinh (dd/mm/yyyy): ");
    scanf("%d/%d/%d", &a[*n].ngay_sinh_chuTK.day, &a[*n].ngay_sinh_chuTK.month, &a[*n].ngay_sinh_chuTK.year);
    printf("Nhap so CCCD/CMND: ");
    scanf("%s", &a[*n].cmnd);
    a[*n].flag = 0;
    a[*n].BD_soDu[0].trans_day = specify_today();
    a[*n].BD_soDu[0].trans_type = 1;
    a[*n].BD_soDu[0].trans_amount = 50000;
    a[*n].BD_soDu[0].current_balance = 50000;
    a[*n].soDu = 50000;
    a[*n].soBD = 1;
    printf("\n>> Tao tai khoan thanh cong <<");
    printf("\nSTK: %s", a[*n].soTK);
    printf("\nMK: %s", a[*n].MK);
    printf("\nNgay tao: %d/%d/%d", a[*n].ngay_taoTK.day, a[*n].ngay_taoTK.month, a[*n].ngay_taoTK.year);
    printf("\nTen chu TK: %s", a[*n].ten_chuTK);
    printf("\nNgay sinh: %d/%d/%d", a[*n].ngay_sinh_chuTK.day, a[*n].ngay_sinh_chuTK.month, a[*n].ngay_sinh_chuTK.year);
    printf("\nSo CMND: %s", a[*n].cmnd);
    printf("\nSo du: %.0lf", a[*n].soDu);
    printf("\n>> Hay dang nhap lai <<");
    *n += 1;
}

void transaction(cus a[], int n, int x)
{
    int sw, sw1 = 0;
    double t;
    printf("\n       -----Giao dich-----");
    printf("\nNhap loai giao dich (1-Gui tien;0-Rut tien): ");
    scanf("%d", &sw);
    printf("Nhap số tien giao dich: ");
    scanf("%lf", &t);
    printf("\nXac nhan giao dich");
    if (sw == 1)
        printf("\nLoai giao dich: Gui tien");
    else
        printf("\nLoai giao dich: Rut tien");
    printf("\nSo tien: %.0lf", t);
    printf("\n(1-Dong y; 0-Tu choi) ");
    scanf("%d", &sw1);
    if (sw1 == 1)
    {
        int y = a[x].soBD;
        a[x].BD_soDu[y].trans_day = specify_today();
        a[x].BD_soDu[y].trans_type = sw;
        a[x].BD_soDu[y].trans_amount = t;
        if (sw == 1)
        {
            a[x].BD_soDu[y].current_balance = a[x].soDu + t;
            a[x].BD_soDu[y].trans_type = 1;
        }
        else
        {
            if (a[x].soDu < t)
            {
                printf("\n>>> Giao dich thất bai, so du khong đu <<<");
                return;
            }
            a[x].BD_soDu[y].current_balance = a[x].soDu - t;
            a[x].BD_soDu[y].trans_type = 0;
        }
        a[x].soDu = a[x].BD_soDu[y].current_balance;
        a[x].soBD++;
        printf("\n>>> Giao dich thanh cong <<<");
        printf("\nSo du hien tai: %.0lf", a[x].soDu);
    }
    else
        printf("\n>>> Huy giao dich <<<");
}

void infor(cus a[], int n, int x)
{
    printf("\n-----Thong tin tai khoan-----");
    printf("\nSo tai khoan: %s", a[x].soTK);
    printf("\nMat khau: %s", a[x].MK);
    printf("\nNgay tao tai khoan: %d/%d/%d", a[x].ngay_taoTK.day, a[x].ngay_taoTK.month, a[x].ngay_taoTK.year);
    printf("\nTen chu TK: %s", a[x].ten_chuTK);
    printf("\nNgay sinh: %d/%d/%d", a[x].ngay_sinh_chuTK.day, a[x].ngay_sinh_chuTK.month, a[x].ngay_sinh_chuTK.year);
    printf("\nSo CMND: %s", a[x].cmnd);
}

void inforSettings(cus a[], int n, int x)
{
    int sw, d, m, y;
    char mk[7], name[20], cmnd[10];
    printf("\n-----Sua doi thong tin-----");
    printf("\nNhap thong tin muon sua");
    printf("\n1 - Mat khau");
    printf("\n2 - Ten chu TK");
    printf("\n3 - Ngay sinh");
    printf("\n4 - So CMND");
    printf("\n5 - Thoat");
    printf("\n>>> ");
    scanf("%d", &sw);
    switch (sw)
    {
    case 1:
    {
        printf("\nNhap MK moi: ");
        scanf("%s", &mk);
        while (strcmp(mk, a[x].MK) == 0)
        {
            printf("MK moi khong duoc trung voi MK cu, nhap lai: ");
            scanf("%s", &mk);
        }
        strcpy(a[x].MK, mk);
        printf(">> Doi MK thanh cong <<");
        printf("\n%s", a[x].MK);
        break;
    }
    case 2:
    {
        printf("\nNhap Ten moi: ");
        fgets(name, sizeof(name), stdin);
        name[strcspn(name, "\n")] = '\0';
        strcpy(a[x].ten_chuTK, name);
        printf(">> Doi ten thanh cong <<");
        break;
    }
    case 3:
    {
        printf("\nNhap ngay sinh moi: ");
        scanf("%d/%d/%d", &d, &m, &y);
        a[x].ngay_sinh_chuTK.day = d;
        a[x].ngay_sinh_chuTK.month = m;
        a[x].ngay_sinh_chuTK.year = y;
        printf(">> Doi ngay sinh thanh cong <<");
        break;
    }
    case 4:
    {
        printf("\nNhap so CMND moi: ");
        scanf("%s", &cmnd);
        strcpy(a[x].cmnd, cmnd);
        printf(">> Doi so CMND thanh cong <<");
        break;
    }
    case 5:
    {
        break;
    }
    }
    return;
}

void trans_history(cus a[], int n, int x)
{
    printf("\n----- Lich su bien dong so du -----\n");
    int b = 1;
    for (int i = a[x].soBD - 1; i > -1; i--)
    {
        printf("\n........Giao dich %d........", b);
        printf("\nNgay: %d/%d/%d", a[x].BD_soDu[i].trans_day.day, a[x].BD_soDu[i].trans_day.month, a[x].BD_soDu[i].trans_day.year);
        printf("\nLoai giao dich: ");
        if (a[x].BD_soDu[i].trans_type == 1)
            printf("Gui tien");
        else
            printf("Rut tien");
        printf("\nSo tien giao dich: %.0lf", a[x].BD_soDu[i].trans_amount);
        printf("\nSo du %.0lf", a[x].BD_soDu[i].current_balance);
        printf("\n");
        b++;
    }
}

void deleteAccount(cus a[], int *n, int x)
{
    int sw;
    printf("\n-Ban co chac la muon xoa tai khoan nay khong-");
    printf("\n 1 - Dong y");
    printf("\n 2 - Huy");
    printf("\n>>> ");
    scanf("%d", &sw);
    if (sw == 1)
    {
        for (int i = x; i < *n; i++)
        {
            a[i] = a[i + 1];
        }
        *n -= 1;
        printf("\n-Xoa tai khoan thanh cong-");
    }
    else
    {
        printf("\n-Huỷ thao tác-");
    }
}

void backupData(cus a[], ad adm[], int n, int nn)
{
    FILE *f = fopen("banking.txt", "w");
    fprintf(f, "Banking System\n");
    for (int i = 0; i < nn; i++)
    {
        fprintf(f, "#%s|%s|%d/%d/%d|%s\n", adm[i].tenTK, adm[i].mk, adm[i].ngay_taoTK.day, adm[i].ngay_taoTK.month,
                adm[i].ngay_taoTK.year, adm[i].tenAd);
    }
    for (int i = 0; i < n; i++)
    {
        fprintf(f, "=%s|%s|%d/%d/%d|%s|%d/%d/%d|%s|%d|", a[i].soTK, a[i].MK,
                a[i].ngay_taoTK.day, a[i].ngay_taoTK.month, a[i].ngay_taoTK.year,
                a[i].ten_chuTK, a[i].ngay_sinh_chuTK.day, a[i].ngay_sinh_chuTK.month, a[i].ngay_sinh_chuTK.year,
                a[i].cmnd, a[i].flag);
        for (int j = 0; j < a[i].soBD; j++)
        {
            fprintf(f, "*%d/%d/%d-%d-%.0lf-%.0lf", a[i].BD_soDu[j].trans_day.day, a[i].BD_soDu[j].trans_day.month, a[i].BD_soDu[j].trans_day.year,
                    a[i].BD_soDu[j].trans_type, a[i].BD_soDu[j].trans_amount, a[i].BD_soDu[j].current_balance);
        }
        fprintf(f, "\n");
    }
    fclose(f);
}

void menu_cus(cus a[], ad adm[], int n, int nn)
{
    int sw1, sw2 = 0, x;
    while (1)
    {
        printf("\n\n-----------------------------------------");
        printf("\n   CAC CHUC NANG DANH CHO KHACH HANG");
        printf("\n 1 - Dang nhap tai khoan");
        printf("\n 2 - Tao tai khoan");
        printf("\n 3 - Giao dich");
        printf("\n 4 - Xem thong tin tai khoan");
        printf("\n 5 - Thiet lap thong tin tai khoan");
        printf("\n 6 - Lich su bien dong so du");
        printf("\n 7 - Xoa tai khoan");
        printf("\n 8 - Thoat");
        printf("\nNhap chuc nang: ");
        scanf("%d", &sw1);
        switch (sw1)
        {
        case 1:
        {
            x = login(a, n);
            sw2 = 1;
            if (x == -1)
                backupData(a, adm, n, nn);
            break;
        }
        case 2:
        {
            if (sw2 == 1)
                printf("\nError");
            else
            {
                createAccount(a, &n);
            }
            break;
        }
        case 3:
        {
            if (sw2 == 0)
                printf("\nHay dang nhap tai khoan ngan hang truoc");
            else
                transaction(a, n, x);
            break;
        }
        case 4:
        {
            if (sw2 == 0)
                printf("\nHay dang nhap tai khoan ngan hang truoc");
            else
                infor(a, n, x);
            break;
        }
        case 5:
        {
            if (sw2 == 0)
                printf("\nHay dang nhap tai khoan ngan hang truoc");
            else
                inforSettings(a, n, x);
            break;
        }
        case 6:
        {
            if (sw2 == 0)
                printf("\nHay dang nhap tai khoan ngan hang truoc");
            else
                trans_history(a, n, x);
            break;
        }
        case 7:
        {
            if (sw2 == 0)
                printf("\nHay dang nhap tai khoan ngan hang truoc");
            else
                deleteAccount(a, &n, x);
            break;
        }
        case 8:
        {
            printf("\n--Ket thuc phien lam viec--");
            sw1 = 0;
            break;
        }
        }
        if (sw1 == 0 || x == -1)
        {
            backupData(a, adm, n, nn);
            return;
        }
    }
}

void cus_list(cus a[], ad adm[], int n, int nn)
{
    printf("\n----- Danh sach tai khoan ngang hang -----");
    printf("\n+-----+---------------+---------------+---------------+-----------+------------+");
    printf("\n| STT | So tai khoan  | Ngay lap TK   | Ten chu TK    | So CMND   | Tinh trang |");
    printf("\n+-----+---------------+---------------+---------------+-----------+------------+");
    for (int i = 0; i < n; i++)
    {
        printf("\n| %-4d| %-14s| %-2d/%-2d/%-4d    | %-14s| %-10s",
               i + 1, a[i].soTK, a[i].ngay_taoTK.day, a[i].ngay_taoTK.month, a[i].ngay_taoTK.year, a[i].ten_chuTK, a[i].cmnd);
        if (a[i].flag == 1)
            printf("| Bi khoa    |");
        else
            printf("| Ko bi khoa |");
        printf("\n+-----+---------------+---------------+---------------+-----------+------------+");
    }
}

void ad_list(ad adm[], int nn)
{
    printf("\n----- Danh sach tai khoan QTV -----");
    printf("\n+-----+---------------+---------------+---------------+");
    printf("\n| STT | Ten tai khoan | Ngay lap TK   | Ten Admin     |");
    printf("\n+-----+---------------+---------------+---------------+");
    for (int i = 0; i < nn; i++)
    {
        printf("\n| %-4d| %-14s| %-2d/%-2d/%-4d    | %-14s|", i + 1,
               adm[i].tenTK, adm[i].ngay_taoTK.day, adm[i].ngay_taoTK.month, adm[i].ngay_taoTK.year, adm[i].tenAd);
        printf("\n+-----+---------------+---------------+---------------+");
    }
}

void lock_acc(cus a[], ad adm[], int n, int nn)
{
    char tk[11];
    printf("\n----- Khoa tai khoan ----");
    printf("\n Nhap so tai khoan muốn khoa: ");
    scanf("%s", &tk);
    int x = -1;
    for (int i = 0; i < n; i++)
    {
        if (strcmp(a[i].soTK, tk) == 0)
            x = i;
    }
    while (x == -1)
    {
        printf("So TK khong ton tai, nhap lai: ");
        scanf("%s", &tk);
        for (int i = 0; i < n; i++)
        {
            if (strcmp(a[i].soTK, tk) == 0)
                x = i;
        }
    }
    a[x].flag = 1;
    printf("\n>>> Khoa tai khoan thanh cong <<<");
}

void unlock_acc(cus a[], ad adm[], int n, int nn)
{
    char tk[11];
    printf("\n----- Mo khoa tai khoan ----");
    printf("\n Nhap so tai khoan muon mo khoa: ");
    scanf("%s", &tk);
    int x = -1;
    for (int i = 0; i < n; i++)
    {
        if (strcmp(a[i].soTK, tk) == 0)
            x = i;
    }
    while (x == -1)
    {
        printf("So TK khong ton tai, nhap lai: ");
        scanf("%s", &tk);
        for (int i = 0; i < n; i++)
        {
            if (strcmp(a[i].soTK, tk) == 0)
                x = i;
        }
    }
    a[x].flag = 0;
    printf("\n>>> Mo khoa tai khoan thanh cong <<<");
}

void add_acc(ad adm[], int *nn, int w)
{
    int sw, r, sw1;
    if (w != 0)
    {
        printf("\n---- Tai khoan cua ban khong co quyen thuc hien chuc nang nay ----");
        return;
    }
    printf("\n----- Them/Xoa tai khoan Admin -----");
    printf("\n 1 - Them tai khoan");
    printf("\n 2 - Xoa tai khoan");
    printf("\n>>> ");
    scanf("%d", &sw);
    if (sw == 1)
    {
        char newAcc[9];
        srand((unsigned int)time(NULL));
        do
        {
            strcpy(newAcc, "Ad");
            char s[7];
            r = GetRandom(100000, 999999);
            itoa(r, s, 10);
            strcat(newAcc, s);
            printf("\nTen tai khoan de xuat: %s", newAcc);
            printf("\n 1 - Dong y");
            printf("\n 2 - Ten khac");
            printf("\n>>> ");
            scanf("%d", &sw1);
        } while (sw1 == 2);
        strcpy(adm[*nn].tenTK, newAcc);
        printf("Nhap mat khau: ");
        scanf("%s", adm[*nn].mk);
        while (strlen(adm[*nn].mk) != 6)
        {
            printf("Nhap lai mat khau: ");
            scanf("%s", &adm[*nn].mk);
        }
        fflush(stdin);
        printf("Nhap ten Admin: ");
        scanf("%s", &adm[*nn].tenAd);
        adm[*nn].ngay_taoTK = specify_today();
        printf("\n>>> Them tai khoan QTV thanh cong <<<");
        *nn += 1;
    }
    else
    {
        char tk[9];
        printf("\nNhap so tai khoan muon xoa: ");
        scanf("%s", &tk);
        int x = -1;
        for (int i = 0; i < *nn; i++)
        {
            if (strcmp(adm[i].tenTK, tk) == 0)
                x = i;
        }
        while (x == -1)
        {
            printf("So TK khong ton tai, nhap lai: ");
            scanf("%s", &tk);
            for (int i = 0; i < *nn; i++)
            {
                if (strcmp(adm[i].tenTK, tk) == 0)
                    x = i;
            }
        }
        printf("\n--Xac nhan xoa tai khoan %s--", adm[x].tenTK);
        printf("\n 1 - Xac nhan");
        printf("\n 2 - Huy");
        printf("\n>>> ");
        scanf("%d", &sw1);
        if (sw1 == 1)
        {
            for (int i = x; i < *nn; i++)
            {
                adm[i] = adm[i + 1];
            }
            *nn -= 1;
            printf("\n>>> Xoa tai khoan thanh cong <<<");
        }
        else
        {
            printf("\n>>> Huy thao tac <<<");
            return;
        }
    }
}

void menu_ad(cus a[], ad adm[], int n, int nn)
{
    char tk[9], mk[7];
    int w = -1;
    // printf("\nn%d", n);
    // printf("\nnn%d", nn);
    printf("\n--- Hay dang nhap tai khoan quan tri vien ---");
    printf("\nNhap ten tai khoan: ");
    scanf("%s", &tk);
    for (int i = 0; i < nn; i++)
    {
        if (strcmp(adm[i].tenTK, tk) == 0)
            w = i;
    }
    while (w == -1)
    {
        printf("Tai khoan khong ton tai, nhap lai: ");
        scanf("%s", &tk);
        for (int i = 0; i < nn; i++)
        {
            if (strcmp(adm[i].tenTK, tk) == 0)
                w = i;
        }
    }
    printf("Nhap mat khau: ");
    scanf("%s", &mk);
    while (strcmp(adm[w].mk, mk) != 0)
    {
        printf("Mat khau khong dung, nhap lai: ");
        scanf("%s", &mk);
    }
    printf("\n>>> Dang nhap thanh cong <<<");
    printf("\n  Xin chao %s", adm[w].tenAd);
    int sw, sw1 = 0;
    while (1)
    {
        printf("\n\n===== CAC CHUC NANG DANH CHO QUAN TRI VIEN =====");
        printf("\n 1 - Danh sach cac tai khoan ngan hang");
        printf("\n 2 - Danh sach cac tai khoan QTV");
        printf("\n 3 - Khoa tai khoan NH");
        printf("\n 4 - Mo khoa tai khoan NH");
        printf("\n 5 - Them, xoa tai khoan QTV");
        printf("\n 6 - Thoat");
        printf("\nNhap chuc nang: ");
        scanf("%d", &sw);
        switch (sw)
        {
        case 1:
            cus_list(a, adm, n, nn);
            break;
        case 2:
            ad_list(adm, nn);
            break;
        case 3:
            lock_acc(a, adm, n, nn);
            sw1 = 1;
            break;
        case 4:
            unlock_acc(a, adm, n, nn);
            sw1 = 1;
            break;
        case 5:
            add_acc(adm, &nn, w);
            sw1 = 1;
            break;
        case 6:
            printf("\n----- Ket thuc -----");
            break;
        }
        if (sw1 == 1 && sw == 6)
        {
            backupData(a, adm, n, nn);
            return;
        }
    }
}

int main()
{
    char tk[11];
    int sw1, sw2 = 0, x;
    cus a[100];
    ad adm[100];
    printf("\n+=================================================+");
    printf("\n|         CHUONG TRINH HE THONG NGAN HANG         |");
    printf("\n+=================================================+");
    while (1)
    {
        int n = input_cus(a);
        int nn = input_ad(adm);
        int sw;
        printf("\n\nMenu chuc nang");
        printf("\n========================================");
        printf("\n 1 - Chuc nang cho khach hang");
        printf("\n 2 - Chuc nang cho quan tri vien");
        printf("\n 3 - Thoat");
        printf("\nNhap chuc nang: ");
        scanf("%d", &sw);
        switch (sw)
        {
        case 1:
            menu_cus(a, adm, n, nn);
            break;
        case 2:
            menu_ad(a, adm, n, nn);
            break;
        case 3:
            printf("\n~~~~~~~ Ket thuc chuong trinh ~~~~~~~");
            return 0;
        }
    }
    return 0;
}