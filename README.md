# Запуск

## Локально

1. Склонировать репозиторий
2. Установить библиотеку
```bash
sudo apt-get install libncurses-dev
```
3. Создать папку build
```bash
mkdir build
cd build
```
4. Собрать проект
```bash
cmake ..
make
```
5. Запустить 
```bash
./app
```

## Через Docker

Т.к. приложение работает только на Linux в репозитории есть Dockerfile и работу приложения можно посмотреть прямо в докере:
```bash
docker build . -t editor
docker run -it editor
```
Откроется командная оболочка внутри контейнера, там можно запустить приложение
```bash
./app
```

# Работа с приложением

1. Для набора текста доступны только английские буквы, клавиши Enter и Backspace и стрелки вверх, вниз, влево, вправо
2. Выход из приложения - Ctrl + C
3. Вход в меню - Ctrl + A

# Демо

https://drive.google.com/file/d/1wZlKumtKKZomRZi2oAqTLVtVbEFoEoQq/view?usp=sharing
