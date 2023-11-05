#!/bin/bash

# Функция для рекурсивного обхода директорий
function process_directory {
    local dir="$1"
    local extension="$2"

    # Проверяем, если текущая директория - 'build', то пропускаем ее
    if [ "$(basename "$dir")" == "build" ]; then
        return
    fi

    # Вход в директорию
    cd "$dir" || return

    # Получаем список файлов и сортируем их по алфавиту
    local files
    if [ -n "$extension" ]; then
        files=$(find . -maxdepth 1 -type f -name "*.$extension" | sort)
    else
        files=$(find . -maxdepth 1 -type f -regex '.*\.\(cpp\|hpp\)' | sort)
    fi

    # Выводим файлы
    for file in $files; do
        echo "Путь к файлу: $file"
        echo "Название файла: $(basename "$file")"
        echo "Содержимое файла:"
        echo "---------------------------------------------"
        cat "$file"
        echo "---------------------------------------------"
        echo
    done

    # Рекурсивно обрабатываем поддиректории, если они существуют
    local subdirs
    subdirs=$(find . -mindepth 1 -maxdepth 1 -type d | sort)
    if [ -n "$subdirs" ]; then
        for subdir in $subdirs; do
            process_directory "$subdir" "$extension"
        done
    fi

    # Возвращаемся на уровень выше
    cd ..
}

# Проверяем наличие аргумента для расширения
if [ $# -eq 0 ]; then
    extension=""
elif [ "$1" == "cpp" ]; then
    extension="cpp"
elif [ "$1" == "hpp" ]; then
    extension="hpp"
else
    echo "Поддерживаются только аргументы 'cpp' и 'hpp' или отсутствие аргументов для вывода всех файлов."
    exit 1
fi

# Вызываем функцию для начальной директории
process_directory . "$extension"
