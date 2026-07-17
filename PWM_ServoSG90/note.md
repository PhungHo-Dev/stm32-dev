# Điều khiển Servo bằng PWM (TIM2)

## 1. Giới thiệu

Dùng **TIM2 Channel 1** tạo xung PWM để điều khiển góc quay servo (0° - 180°).

## 2. Cấu hình Timer

- Prescaler = 63, Period = 19999 → tần số PWM ~50Hz (chu kỳ 20ms, chuẩn cho servo)
- Mode: PWM1, Polarity: High
- Ngõ ra qua chân TIM2_CH1 (cấu hình alternate function trong `HAL_TIM_MspPostInit`)

## 3. Nguyên lý điều khiển

Servo thường nhận xung điều khiển 1ms - 2ms trong chu kỳ 20ms:
- **1ms** → góc 0°
- **2ms** → góc 180°

Hàm `servo_Write(pwm)` quy đổi góc (0-180) sang giá trị CCR tương ứng (1000-2000, đơn vị us vì 1 tick = 1us):

```c
CCR1 = (1000 * pwm) / 180 + 1000;
```

## 4. Ghi chú

- Cần gọi `servo_Init()` (Start PWM) trước khi dùng `servo_Write()`.
- Test nhanh trong `main()`: quay 0° → delay 1s → quay 180° → delay 1s, lặp lại.
- Nếu servo giật/rung, kiểm tra nguồn cấp servo (thường cần dòng riêng, không nên lấy trực tiếp từ STM32).
