package main

import (
	"crypto/rand"
	"crypto/rsa"
	"crypto/x509"
	"encoding/pem"
	"fmt"
	"io"
	"io/ioutil"
	"log"
	"net/http"
	"net/url"
)

// ReadPrivateKey 从文件中读取私钥
func ReadPrivateKey(filename string) (*rsa.PrivateKey, error) {
	privateKeyPEM, err := ioutil.ReadFile(filename)
	if err != nil {
		return nil, err
	}
	block, _ := pem.Decode(privateKeyPEM)
	if block == nil {
		return nil, fmt.Errorf("no PEM block found in private key file")
	}
	privateKeyRead, err := x509.ParsePKCS1PrivateKey(block.Bytes)
	if err != nil {
		return nil, err
	}
	return privateKeyRead, nil
}

// DecryptData 使用私钥解密数据
func DecryptData(privateKey *rsa.PrivateKey, cipherText []byte) ([]byte, error) {
	return rsa.DecryptPKCS1v15(rand.Reader, privateKey, cipherText)
}

func handleRequest(w http.ResponseWriter, r *http.Request) {
	// 解析原始请求的 URL
	url, err := url.Parse(r.URL.String())
	if err != nil {
		http.Error(w, err.Error(), http.StatusBadRequest)
		return
	}

	queryParams := r.URL.Query()
	// 获取特定的查询参数
	im_token_request := queryParams.Get("im_token_request")
	log.Printf("Failed to read private key: %s", im_token_request)

	// 从文件中读取私钥
	privateKeyRead, err := ReadPrivateKey("privateKey.pem")
	if err != nil {
		log.Fatalf("Failed to read private key: %v", err)
	}

	// 使用读取的私钥解密数据
	tokenBytes := []byte(im_token_request)
	plainText, err := DecryptData(privateKeyRead, tokenBytes)
	if err != nil {
		log.Fatalf("Failed to decrypt data: %v", err)
	}

	vetifykvalue := "im_token_request"
	decodeVerify := string(plainText)
	if decodeVerify != vetifykvalue {
		log.Printf("Failed to decrypt data")
		return
	}

	// 修改 URL 的 Host 或其他部分
	url.Host = "101.43.53.16:8081"
	url.Scheme = "http" // 确保设置了正确的 Scheme

	// 创建新的请求
	newReq, err := http.NewRequest(r.Method, url.String(), r.Body)
	if err != nil {
		http.Error(w, err.Error(), http.StatusInternalServerError)
		return
	}
	newReq.Header = r.Header

	// 创建 http.Client 发送请求
	client := &http.Client{}
	resp, err := client.Do(newReq)
	if err != nil {
		http.Error(w, err.Error(), http.StatusServiceUnavailable)
		return
	}
	defer resp.Body.Close()

	// 将响应转发回客户端
	for k, v := range resp.Header {
		w.Header().Set(k, v[0])
	}
	w.WriteHeader(resp.StatusCode)
	io.Copy(w, resp.Body)
}

func main() {
	http.HandleFunc("/", handleRequest)
	log.Fatal(http.ListenAndServe(":8080", nil))
}
