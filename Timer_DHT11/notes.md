# Timer & DHT11 - STM32F103

## 1. Giới thiệu

Bài này kết hợp 2 phần:
- Dùng **Timer (TIM1)** để tạo ngắt định kỳ, toggle LED (PA1) mỗi khi tràn.
- Dùng **Timer (TIM2)** làm delay us chính xác, phục vụ đọc dữ liệu từ cảm biến **DHT11** (chân PA2).

---

## 2. Sơ đồ kết nối

| Chân STM32 | Chức năng                     |
|------------|--------------------------------|
| PA1        | Output - toggle LED (qua ngắt TIM1) |
| PA2        | I/O - giao tiếp DHT11 (1 dây, đổi chiều input/output) |

---

## 3. Cấu hình Timer

### TIM1 - Ngắt định kỳ
- Prescaler = 0, Period = 499
- Clock source: Internal
- Dùng `HAL_TIM_Base_Start_IT()`, xử lý trong callback `HAL_TIM_PeriodElapsedCallback()`
- Mỗi lần tràn → toggle chân PA1

### TIM2 - Delay vi giây (us)
- Prescaler = 63, Period = 65535
- Dùng làm đồng hồ đếm cho hàm `delay_us()`:
  - Start timer, reset CNT về 0
  - Chờ đến khi `CNT >= time_us`
  - Stop timer
- Hàm `delay_ms()` gọi `delay_us(1000)` lặp lại theo số ms cần

---

## 4. Giao thức đọc DHT11

DHT11 giao tiếp qua **1 dây duy nhất** (chân PA2), cần đổi chiều input/output liên tục:

1. **`DHT11_Start()`**: 
   - Set chân thành Output, kéo xuống LOW ~20ms để "đánh thức" cảm biến
   - Kéo lên HIGH, chuyển chân thành Input
   - Chờ cảm biến phản hồi (xuống 0 → lên 1 → xuống 0), bắt đầu truyền 40 bit dữ liệu

2. **`DHT11_Read()`**: đọc từng byte (8 bit)
   - Mỗi bit: chờ mức HIGH, delay 50us, đọc mức tín hiệu
     - Nếu vẫn HIGH sau 50us → bit = 1
     - Nếu đã xuống LOW → bit = 0
   - Chờ tín hiệu xuống LOW trước khi đọc bit tiếp theo

3. **`DHT11_Handle()`**: đọc đủ 5 byte theo thứ tự
   - Byte 1: bỏ qua (response bit)
   - Byte 2: phần nguyên độ ẩm (`int_hum`)
   - Byte 3: phần thập phân độ ẩm (`float_hum`)
   - Byte 4: phần nguyên nhiệt độ (`int_tem`)
   - Byte 5: phần thập phân nhiệt độ (`float_tem`)
   - Byte 6: checksum (kiểm tra tổng 4 byte trước)

---
