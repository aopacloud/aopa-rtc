package main

import (
	"fmt"
	"log"
	"net/http"
)

// 定义请求处理函数
func helloHandler(w http.ResponseWriter, r *http.Request) {
	// 发送响应状态码
	w.WriteHeader(http.StatusOK)
	// 发送响应头
	w.Header().Set("Content-Type", "text/plain")
	// 发送响应体
	fmt.Fprintf(w, "Hello, world 8081!")
}

func main4() {
	// 设置路由
	http.HandleFunc("/", helloHandler)
	// 定义服务器要监听的地址和端口
	addr := ":8081"
	// 启动服务器
	log.Printf("Server starting on %s\n", addr)
	if err := http.ListenAndServe(addr, nil); err != nil {
		log.Fatal("ListenAndServe error: ", err)
	}
}
