# LCD1602 - Giao tiếp 8-bit với STM32

## 1. Giới thiệu

LCD1602 là màn hình ký tự 16x2, có thể hiển thị:

- 2 hàng
- Mỗi hàng 16 ký tự
- Tổng cộng 32 ký tự

Bên trong LCD sử dụng controller HD44780 nên cách điều khiển gần như giống nhau giữa các loại LCD1602.

Trong project này sử dụng **chế độ giao tiếp 8-bit**, nghĩa là STM32 truyền toàn bộ 8 bit dữ liệu cùng lúc.

---

# 2. Sơ đồ kết nối

| Chân LCD | Chức năng | Kết nối STM32 |
|----------|-----------|---------------|
| VSS | GND | GND |
| VDD | Nguồn 5V | 5V |
| V0 | Điều chỉnh độ tương phản | Biến trở 10K |
| RS | Register Select | PB0 |
| RW | Read / Write | PB1 |
| E | Enable | PB10 |
| D0 | Data bit 0 | PA0 |
| D1 | Data bit 1 | PA1 |
| D2 | Data bit 2 | PA2 |
| D3 | Data bit 3 | PA3 |
| D4 | Data bit 4 | PA4 |
| D5 | Data bit 5 | PA5 |
| D6 | Data bit 6 | PA6 |
| D7 | Data bit 7 | PA7 |
| LED+ | Đèn nền | 5V |
| LED- | Đèn nền | GND |

---

# 3. Các chân điều khiển

## RS (Register Select)

Chọn thanh ghi mà LCD sẽ làm việc.

### RS = 0

Gửi **Command**.

Ví dụ:

- Xóa màn hình
- Di chuyển con trỏ
- Khởi tạo LCD

Ví dụ:

```c
LCD_write_cmd(0x01);
```

---

### RS = 1

Gửi **Data**.

Data chính là ký tự muốn hiển thị.

Ví dụ:

```c
LCD_write_data('A');
```

LCD sẽ hiển thị ký tự **A**.

---

## RW (Read / Write)

Điều khiển hướng truyền dữ liệu.

| RW | Ý nghĩa |
|----|----------|
| 0 | Ghi dữ liệu vào LCD |
| 1 | Đọc dữ liệu từ LCD |

Trong hầu hết project STM32 cơ bản:

```text
RW luôn nối GND
```

vì chỉ cần ghi dữ liệu.

---

## E (Enable)

Enable giống như nút **xác nhận**.

Sau khi:

- đặt RS
- đặt dữ liệu lên D0-D7

STM32 tạo xung:

```
0
↓
1
↓
0
```

LCD sẽ chốt dữ liệu tại cạnh xuống của chân E.

---

# 4. Bus dữ liệu D0-D7

Đây là 8 đường truyền dữ liệu.

Ví dụ gửi:

```text
'A'
```

ASCII của A là

```
65
```

hay

```
01000001
```

STM32 sẽ xuất:

```
D7 D6 D5 D4 D3 D2 D1 D0

0  1  0  0  0  0  0  1
```

Sau đó tạo xung Enable để LCD nhận dữ liệu.

---

# 5. Command và Data

LCD có hai loại dữ liệu:

## Command

Là lệnh điều khiển LCD.

Ví dụ:

| Command | Chức năng |
|----------|-----------|
| 0x01 | Clear Display |
| 0x02 | Return Home |
| 0x06 | Entry Mode |
| 0x0C | Display ON |
| 0x38 | 8-bit, 2 dòng |

Ví dụ:

```c
LCD_write_cmd(0x01);
```

LCD sẽ xóa toàn bộ màn hình.

---

## Data

Data là ký tự cần hiển thị.

Ví dụ:

```c
LCD_write_data('H');
LCD_write_data('e');
LCD_write_data('l');
LCD_write_data('l');
LCD_write_data('o');
```

Màn hình sẽ hiển thị:

```
Hello
```

---

# 6. Trình tự gửi dữ liệu

## Gửi Command

```
RS = 0

↓

Đặt dữ liệu lên D0-D7

↓

Tạo xung E

↓

LCD thực hiện lệnh
```

---

## Gửi Data

```
RS = 1

↓

Đặt dữ liệu lên D0-D7

↓

Tạo xung E

↓

LCD hiển thị ký tự
```

---

# 7. Các hàm trong project

```c
LCD_init();
```

Khởi tạo LCD.

---

```c
LCD_write_cmd(cmd);
```

Gửi lệnh điều khiển.

---

```c
LCD_write_data(data);
```

Hiển thị một ký tự lên LCD.

---

```c
LCD_write_byte(data, mode);
```

Hàm mức thấp (low-level) dùng để gửi một byte đến LCD.

- `mode = 0` → Command
- `mode = 1` → Data

Hai hàm `LCD_write_cmd()` và `LCD_write_data()` đều gọi lại hàm này.

---

# 8. Kiến thức rút ra

- LCD1602 sử dụng controller HD44780.
- LCD có hai thanh ghi: **Command Register** và **Data Register**.
- RS quyết định gửi **Command** hay **Data**.
- RW quyết định **Read** hoặc **Write**.
- E dùng để chốt dữ liệu.
- Ở chế độ 8-bit, STM32 truyền toàn bộ dữ liệu qua D0-D7 trong một lần.
- Hầu hết ứng dụng cơ bản chỉ sử dụng chế độ **Write**, vì vậy chân RW thường nối GND.
