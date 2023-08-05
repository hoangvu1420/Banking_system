# Chương trình giả lập hệ thống quản lí tài khoản ngân hàng

**Chương trình thực hiện một số thao tác cơ bản trong việc quản lí tài khoản tiết kiệm ở ngân hàng. Chương trình được viết bằng ngôn ngữ C và gia tiếp qua màn hình nhập xuất cơ bản**

## Cấu trúc

- Thông tin các tài khoản tiết kiệm và các tài khoản quản trị được lưu trong một file text. Chương trình sau đó sử dụng một mảng các struct để lưu thông tin các tài khoản đọc được từ file text đó. Sau mỗi lần thực thi, thông tin sẽ được sao lưu lại vào file text. 
- Thông tin của một tài khoản tiết kiệm bao gồm số tài khoản (gồm 11 chữ số), mật khẩu (6 chữ số), tên, ngày sinh, số CMND, ngày lập tài khoản, lịch sử gia dịch,... 
- Thông tin của một tài khoản quản trị bao gồm tên tài khoản (gồm 9 kí tự bắt đầu bằng 'Ad'), mật khẩu (6 kí tự), ngày tạo tài khoản, tên QTV.

## Chức năng

### 1. Chức năng dành cho khách hàng

- Đăng nhập tài khoản, nếu nhập sai mật khẩu quá 5 lần sẽ bị khoá tài khoản.
- Tạo tài khoản mới
- Thực hiện giao dịch
- Xem thông tin tài khoản hiện tại
- Sửa đổi thông tin
- Xem lịch sử biến động số dư
- Xoá tài khoản

### 2. Chức năng dành cho quản trị viên

- Trước hết cần đăng nhập bằng một tài khoản quản trị viên.
- Danh sách các tài khoản ngâng hàng 
- Danh sách các tài khoản QTV
- Khoá tài khoản NH
- Mở khoá tài khoản NH
- Thêm, xoá tài khoản QTV
