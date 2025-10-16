# 🛰️ HRTRANS — Mã hóa và Giải mã thời gian bằng Mã Hamming

## 📘 Giới thiệu
Dự án **HRTRANS** mô phỏng quá trình **mã hóa và giải mã thời gian (HH:MM:SS)** bằng **mã Hamming**, một phương pháp phát hiện và **sửa lỗi 1 bit** trong quá trình truyền dữ liệu.

Chương trình mô phỏng tình huống truyền tin giữa hai thực thể:
- 👨‍✈️ **Captain** — bên mã hóa (bộ phát)
- 🪖 **Soldier** — bên giải mã (bộ thu)

---

## ⚙️ Ý tưởng chính

### 🔹 1. Mục tiêu
Đảm bảo dữ liệu thời gian (giờ, phút, giây) khi truyền đi **an toàn trước lỗi 1 bit**, nhờ cơ chế kiểm tra chẵn lẻ của **Hamming Code**.

### 🔹 2. Nguyên lý hoạt động

1. **Chuyển thời gian sang dạng nhị phân**
   - Giờ (0–23) → 5 bit  
   - Phút (0–59) → 6 bit  
   - Giây (0–59) → 6 bit  
   ➜ Tổng: **17 bit dữ liệu gốc**

2. **Thêm các bit kiểm tra (parity bits)**  
   - Các bit kiểm tra được đặt tại các vị trí là **lũy thừa của 2**:  
     1, 2, 4, 8, 16, …

   - Mỗi bit kiểm tra phụ trách kiểm tra nhóm bit có **vị trí nhị phân chứa bit 1 tương ứng**.

   Ví dụ:
p1 kiểm tra các bit có LSB = 1
p2 kiểm tra các bit có bit thứ 2 = 1
p4 kiểm tra các bit có bit thứ 3 = 1
...
✅ Điều kiện tính số bit kiểm tra:
(với m là số bit dữ liệu gốc, r là số bit kiểm tra)

3. **Phát hiện và sửa lỗi 1 bit**
- Ở phía thu, tính lại các bit parity.  
- Nếu có sai lệch → cộng dồn các vị trí parity sai để xác định **vị trí lỗi**.  
- Đảo bit lỗi để khôi phục dữ liệu gốc.

4. **Giải mã ngược lại sang thời gian (HH:MM:SS)**.

---

## 💡 Ví dụ minh họa

Nhập thời gian (dang HH:MM:SS): 12:03:04
Mã Hamming sau khi mã hóa: 110111000000011110001

Ban có muốn tạo lỗi trong dữ liệu truyền? (y/n): y
Nhập vị trí bit muốn đảo (1 -> 22): 3
Dữ liệu bị lỗi: 111111000000011110001

Thời gian sau khi giải mã: 12:03:04 ✅

> ✅ Chương trình tự động **phát hiện và sửa lỗi** tại vị trí 3.

---

## 🧩 Cấu trúc chương trình
├── HRTRANS.h # Khai báo class Captain và Soldier
├── HRTRANS.cpp # Định nghĩa các hàm encode / decode / hamming
├── main.cpp # Chương trình chính mô phỏng nhập, mã hóa, lỗi, giải mã
└── README.md # Tài liệu mô tả dự án

---

## 🔍 Các lớp chính

### 👨‍✈️ `class Captain`
| Hàm | Chức năng |
|------|------------|
| `to_binary(bits, time)` | Chuyển phần thời gian sang nhị phân |
| `to_hamming(s)` | Sinh mã Hamming (thêm bit kiểm tra) |
| `encode(s)` | Ghép 3 phần (giờ, phút, giây) và tạo mã Hamming hoàn chỉnh |

### 🪖 `class Soldier`
| Hàm | Chức năng |
|------|------------|
| `to_binary(s)` | Phát hiện và sửa lỗi 1 bit trong mã Hamming |
| `to_decimal(s)` | Chuyển chuỗi nhị phân về thập phân |
| `decode(s)` | Tách phần dữ liệu (giờ, phút, giây) và khôi phục thời gian gốc |

---

## 🧮 Công thức xác định lỗi

Sau khi kiểm tra các bit parity:
error_position = Σ (vị trí các parity bit bị sai)
Nếu `error_position != 0`, bit tại vị trí đó bị lỗi → đảo nó lại.

---

## 🧠 Minh họa vị trí bit Hamming (với 17 bit dữ liệu)

| Vị trí | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 | 10 | 11 | 12 | 13 | 14 | 15 | 16 | 17 | 18 | 19 | 20 | 21 | 22 |
|--------|---|---|---|---|---|---|---|---|---|----|----|----|----|----|----|----|----|----|----|----|----|
| Loại bit | P1 | P2 | D1 | P4 | D2 | D3 | D4 | P8 | D5 | D6 | D7 | D8 | D9 | D10 | D11 | P16 | D12 | D13 | D14 | D15 | D16 | D17 |

> 🧩 P: parity bit, D: data bit

---

## 💻 Cách chạy chương trình

### 🔸 Biên dịch
```bash
g++ main.cpp HRTRANS.cpp -o program
🔸 Chạy chương trình
./HRTRANS
📈 Ưu điểm của mã Hamming

✅ Phát hiện và sửa được lỗi 1 bit
✅ Phát hiện lỗi 2 bit (không sửa được)
✅ Hiệu quả cao trong truyền thông và lưu trữ dữ liệu nhạy cảm
