
# Проверка https кодов:
### 1. GET
```
rf9:src$ curl -v http://localhost:32123/

*   Trying 127.0.0.1:32123...
* Connected to localhost (127.0.0.1) port 32123 (#0)
> GET / HTTP/1.1
> Host: localhost:32123
> User-Agent: curl/8.1.2
> Accept: */*
> 
< HTTP/1.1 200 OK
< Content-Length: 299
< Connection: close
< 
<!DOCTYPE html>
<html>
<head>
    <meta charset="UTF-8">
    <title>Main page</title>
    <link rel="stylesheet" href="style.css">
</head>
<body>
  <h1>Static HTTP Server</h1>
  <p>Главная страница</p>
  <a href="page1.html">Перейти на страницу 1</a>
</body>
</html>
* Closing connection 0
```
### 2. HEAD
```
rf9:src$ curl -I http://localhost:32123/      

HTTP/1.1 200 OK
Content-Length: 299
Connection: close
```
### 3. 403 Forbidden (файл без прав на чтение: --w------- files/forbidden.html)
```
rf9:src$ curl -v http://localhost:32123/forbidden.html
*   Trying 127.0.0.1:32123...
* Connected to localhost (127.0.0.1) port 32123 (#0)
> GET /forbidden.html HTTP/1.1
> Host: localhost:32123
> User-Agent: curl/8.1.2
> Accept: */*
> 
< HTTP/1.1 403 Forbidden
< Content-Length: 0
< Connection: close
< 
* Closing connection 0
```
### 4. 404 Not found
```
rf9:src$ curl -v http://localhost:32123/nope.html

*   Trying 127.0.0.1:32123...
* Connected to localhost (127.0.0.1) port 32123 (#0)
> GET /nope.html HTTP/1.1
> Host: localhost:32123
> User-Agent: curl/8.1.2
> Accept: */*
> 
< HTTP/1.1 404 Not Found
< Content-Length: 0
< Connection: close
< 
* Closing connection 0
```
### 5. 405 Method Not Allowed
```
rf9:src$ curl -v -X POST http://localhost:32123/

*   Trying 127.0.0.1:32123...
* Connected to localhost (127.0.0.1) port 32123 (#0)
> POST / HTTP/1.1
> Host: localhost:32123
> User-Agent: curl/8.1.2
> Accept: */*
> 
< HTTP/1.1 405 Method Not Allowed
< Content-Length: 0
< Connection: close
< 
* Closing connection 0
```


# Проверка по контрольной сумме скачанного файла размером 128Мбайт:
```
rf9:src$ shasum -a 256 files/128        
173aa5620fcb6f4047ff78af03b7f32d223bf5fe1c61e00f4fefe8febd9b57b3  files/128
rf9:src$ shasum -a 256 ~/Downloads/128 
173aa5620fcb6f4047ff78af03b7f32d223bf5fe1c61e00f4fefe8febd9b57b3  /Users/rf9/Downloads/128
```
