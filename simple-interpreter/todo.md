# TODO

## 2025/03/25
- C linked list idea

1. 兩個 set，分別為屬於 MST 的 vertex 與 其他的 vertex
2. 隨機找一個 vertex，加入 MST vertex set 裡，當作起始 vertex
3. 從所有 '屬於 MST vertex set 裡的 vertex 連到非 MST 的 vertex 的邊'裡面，找到一個最小 cost 的邊
4. 將此邊加入 MST 裡，並將此非 MST 的 vertex 加到 MST 的 vertex set 裡面
5. 重複步驟 3 與 4，直到所有 vertex 都在 MST vertex set 裡面
