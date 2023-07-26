#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define soLuong 100
struct Date {
    int days;
    int month;
    int year;
};
typedef struct Date date;
typedef struct NhanVien {
    int maNV;
    char ho[50];
    char ten[50];
    date namSinh;
    char noiSinh[100];
    char diaChi[200];
    float luong;
    date ngayVaoLV;
} NhanVien;
struct DanhSach {
    NhanVien a[soLuong];
    int n;
};
typedef struct DanhSach danhSach;

void nhapMotNhanVien(NhanVien &nv) {
    printf("Nhập mã nhân viên:  ");
    scanf("%d", &nv.maNV);

    fflush(stdin);
    printf("Nhập họ nhân viên: ");
    scanf(" %[^\n]", &nv.ho);

    printf("Nhập tên nhân viên: ");
    scanf(" %[^\n]", &nv.ten);

    printf("Nhập ngày sinh nhân viên (dd mm yyyy): ");
    scanf("%d %d %d", &nv.namSinh.days, &nv.namSinh.month, &nv.namSinh.year);

    printf("Nhập nơi sinh nhân viên: ");
    scanf(" %[^\n]", &nv.noiSinh);

    printf("Nhập địa chỉ nhân viên ");
    scanf(" %[^\n]", &nv.diaChi);

    printf("Nhập lương nhân viên ");
    scanf("%f", &nv.luong);

    printf("Nhập ngày vào làm việc: (dd mm yyyy): ");
    scanf("%d %d %d", &nv.ngayVaoLV.days, &nv.ngayVaoLV.month, &nv.ngayVaoLV.year);
}

void xuatMotNhanVien(NhanVien nv) {
    printf("\nMã nhân viên: %d", nv.maNV);
    printf("\nHọ tên nhân viên: %s %s", nv.ho, nv.ten);
    printf("\nNgày sinh nhân viên: %d/%d/%d", nv.namSinh.days, nv.namSinh.month, nv.namSinh.year);
    printf("\nNơi sinh nhân viên: %s", nv.noiSinh);
    printf("\nĐịa chỉ nhân viên: %s", nv.diaChi);
    printf("\nLương nhân viên: %.2f", nv.luong);
    printf("\nNgày vào làm việc: %d/%d/%d", nv.ngayVaoLV.days, nv.ngayVaoLV.month, nv.ngayVaoLV.year);
}

void nhapDanhSach(danhSach &ds) {
    printf("Nhập số lượng nhân viên: ");
    scanf("%d", &ds.n);
    for (int i = 0; i < ds.n; i++) {
        printf("Nhập thông tin nhân viên thứ %d:\n", i + 1);
        nhapMotNhanVien(ds.a[i]);
    }
};

void xuatDanhSach(danhSach ds) {
    printf("%-5s %-20s %-10s %-15s %-50s %-30s %-10s %-15s %-15s\n", "Mã NV", "Họ", "Tên", "Ngày sinh", "Nơi sinh",
           "Địa chỉ", "Lương", "Ngày vào LV");

    for (int i = 0; i < ds.n; i++) {
        printf("%-5d %-20s %-10s %02d/%02d/%d %-50s %-30s %-10.2f %02d/%02d/%d\n",
               ds.a[i].maNV,
               ds.a[i].ho,
               ds.a[i].ten,
               ds.a[i].namSinh.days,
               ds.a[i].namSinh.month,
               ds.a[i].namSinh.year,
               ds.a[i].noiSinh,
               ds.a[i].diaChi,
               ds.a[i].luong,
               ds.a[i].ngayVaoLV.days,
               ds.a[i].ngayVaoLV.month,
               ds.a[i].ngayVaoLV.year
        );
    }
}

int kiemTraTrungMaNV(DanhSach ds, int maNV) {
    for (int i = 0; i < ds.n; i++) {
        if (ds.a[i].maNV == maNV) {
            return 1; // Trùng mã
        }
    }
    return 0; // Không trùng mã
}

void themNV(DanhSach *ds, NhanVien x, int k) {
    // Kiểm tra nếu danh sách đã đầy
    if (ds->n == soLuong) {
        printf("Danh sach day, khong the them nhan vien moi!\n");
        return;
    }
    // Kiểm tra trùng mã nhân viên
    if (kiemTraTrungMaNV(*ds, x.maNV)) {
        printf("Ma nhan vien da ton tai trong danh sach!\n");
        return;
    }

    // Dịch chuyển các phần tử của danh sách về sau một chỉ mục
    for (int i = ds->n - 1; i >= k; i--) {
        ds->a[i + 1] = ds->a[i];
    }

    // Thêm nhân viên mới vào danh sách tại vị trí k
    ds->a[k] = x;

    // Tăng số lượng nhân viên trong danh sách lên một
    ds->n++;
}

int timTen(danhSach ds, char *c) {
    // Chuyển chuỗi c sang chữ thường
    char lowercase_c[100];
    for (int i = 0; i < strlen(c); i++) {
        lowercase_c[i] = tolower(c[i]);
    }
    lowercase_c[strlen(c)] = '\0';

    for (int i = 0; i < ds.n; i++) {
        // Chuyển tên của nhân viên sang chữ thường
        char lowercase_ten[100];
        for (int j = 0; j < strlen(ds.a[i].ten); j++) {
            lowercase_ten[j] = tolower(ds.a[i].ten[j]);
        }
        lowercase_ten[strlen(ds.a[i].ten)] = '\0';

        if (strcmp(lowercase_ten, lowercase_c) == 0) {
            return i;
            break;
        }
    }
    return -1;
}

int timMa(danhSach ds, int ma) {
    for (int i = 0; i < ds.n; i++) {
        if (ds.a[i].maNV == ma) {
            return i;
        }
    }
    return -1;
}

void selectionSort(danhSach *ds) {
    int n = ds->n;
    for (int i = 0; i < n - 1; i++) {
        int minIndex = i;
        for (int j = i + 1; j < n; j++) {
            if (strcmp(ds->a[j].ten, ds->a[minIndex].ten) < 0) {
                minIndex = j;
            }
        }
        if (minIndex != i) {
            NhanVien temp = ds->a[i];
            ds->a[i] = ds->a[minIndex];
            ds->a[minIndex] = temp;
        }
    }
}

void sapXepTheoLuong(DanhSach *ds) {
    for (int i = 0; i < ds->n - 1; i++) {
        int min_idx = i;
        for (int j = i + 1; j < ds->n; j++) {
            if (ds->a[j].luong > ds->a[min_idx].luong) {
                min_idx = j;
            }
        }
        if (min_idx != i) {
            NhanVien temp = ds->a[i];
            ds->a[i] = ds->a[min_idx];
            ds->a[min_idx] = temp;
        }
    }
}

void xoaNhanVien(DanhSach *ds, int maNV) {
    int viTri = timMa(*ds, maNV); // Tìm vị trí của nhân viên trong danh sách
    if (viTri == -1) { // Nếu không tìm thấy
        printf("Khong tim thay nhan vien co ma so %d\n", maNV);
        return;
    }

    // Dịch chuyển các phần tử của danh sách về trước một chỉ mục từ vị trí tìm được đến hết danh sách
    for (int i = viTri; i < ds->n - 1; i++) {
        ds->a[i] = ds->a[i + 1];
    }

    // Giảm số lượng nhân viên trong danh sách đi một
    ds->n--;
}


void menu() {
    int ch;
    int k;
    NhanVien x;
    danhSach ds;
    nhapDanhSach(ds);
    xuatDanhSach(ds);
    while (true) {
        printf("\n\t\t--------------MENU--------------");
        printf("\n\t 1.Thêm một nhân viên");
        printf("\n\t 2.Tìm 1 nhân viên theo mã nhân viên");
        printf("\n\t 3.Tìm nhân viên theo tên");
        printf("\n\t 4.Bảng lương của nhân viên giảm dần");
        printf("\n\t 5.Xoá 1 nhân viên");
        printf("\n\t **********************************************");
        printf("\n\t Chọn 1 trong những chức năng trên: ");
        scanf("%d", &ch);
        switch (ch) {
            case 1:
                printf("Nhap vi tri can them: ");
                scanf("%d", &k);
                nhapMotNhanVien(x);
                themNV(&ds, x, k);
                printf("Danh sach sau khi them la");
                xuatDanhSach(ds);
                break;
            case 2: {
                char ten[100];
                printf("Nhap ten nhan vien can tim: ");
                scanf("%s", ten);
                fflush(stdin);

                int index = timTen(ds, ten);

                if (index == -1) {
                    printf("Khong tim thay nhan vien co ten la %s\n", ten);
                } else {
                    printf("Nhan vien can tim co ma so la %d\n", ds.a[index].maNV);
                }
                break;
            }
            case 3: {
                int ma;
                printf("Nhap ma nhan vien: ");
                scanf("%d", &ma);
                int index = timMa(ds, ma);
                if (index == -1) {
                    printf("Khong tim thay nhan vien co ma %d\n", ma);
                } else {
                    printf("Thong tin nhan vien co ma %d:\n", ma);
                    xuatMotNhanVien(ds.a[index]);
                }
                break;
            }
            case 4:
                sapXepTheoLuong(&ds);
                xuatDanhSach(ds);
                break;
            case 5:
                int maNV;
                printf("Nhap ma nhan vien can xoa: ");
                scanf("%d", &maNV);
                xoaNhanVien(&ds, maNV);
                printf("Danh sach nhan vien sau khi xoa:\n");
                xuatDanhSach(ds);
                break;
        }
    }

};

int main() {
    menu();
    return 0;
}
