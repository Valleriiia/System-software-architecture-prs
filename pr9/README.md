# Практична робота №9
**Тема:** UNIX/Linux-файлові системи  

---

## Завдання 9.1

Було створено програму, яка використовувала команду `getent passwd` для зчитування облікових записів користувачів. Далі програма аналізувала UID кожного облікового запису, щоб визначити, чи є серед них звичайні користувачі. Залежно від дистрибутиву, UID звичайних користувачів перевищував 500 або 1000. Програма коректно ідентифікувала користувачів, які не були системними або службовими.

**Результат:**  
Серед облікових записів були знайдені звичайні користувачі окрім поточного користувача.

---

## Завдання 9.2

Було написано програму, яка намагалася прочитати файл `/etc/shadow`, запустивши `cat /etc/shadow`. Оскільки звичайний користувач не має прав на пряме читання цього файлу, програма використала команду `sudo`, що дозволяє тимчасово отримати права адміністратора за допомогою пароля.  

**Результат:**  
Програма успішно прочитала файл `/etc/shadow` тільки після введення пароля адміністратора через `sudo`. Без підвищення привілеїв доступ був заборонений.

---

## Завдання 9.3

Програма створила тестовий файл від імені звичайного користувача. Потім, під правами root, було скопійовано цей файл у домашню директорію користувача. Після цього звичайний користувач спробував змінити та зберегти цей файл. При спробі редагування виникла помилка "permission denied", оскільки файл належав root і права на запис для користувача були відсутні.

Потім була здійснена спроба видалення файлу через `rm`. Видалення вдалося, оскільки в Linux важливі права на каталог (наявність права на запис у директорії дозволяє видалити файл навіть без права на зміну його вмісту).

**Висновок:**  
Користувач не міг змінити файл без прав, але зміг його видалити завдяки правам на директорію.

---

## Завдання 9.4

Було створено скрипт, який послідовно запускав команди `whoami` і `id`.  

- `whoami` вивів ім'я користувача, від якого запущено скрипт.  
- `id` показав UID, GID і список груп користувача.  

**Результат:**  
Програма успішно відобразила належність до кількох груп одночасно (наприклад, `users`, `sudo`, `adm`).

---

## Завдання 9.5

Програма створила тимчасовий файл під обліковим записом користувача. Після цього root змінив власника (`chown`) і права доступу (`chmod`).  

Були перевірені сценарії:  
- Файл з правами тільки на читання: користувач міг тільки переглядати вміст.  
- Файл з правами на читання і запис: користувач міг редагувати вміст.  
- Файл без будь-яких прав: доступ до файлу був заборонений.  

**Висновок:**  
Можливість читання чи запису залежала від встановлених прав, незалежно від власника.

---

## Завдання 9.6

Програма виводила списки файлів і їхніх прав через `ls -l` у трьох директоріях:  
- Домашній каталог користувача (`~/`)
- `/usr/bin`
- `/etc`

Далі відбувалась спроба виконання файлів (`./file`), читання (`cat file`) та запису (редагування через `echo text > file`).  

**Результат:**  
- У домашньому каталозі читання, запис та виконання можливі.
- У `/usr/bin` можна було лише виконувати програми, запис заборонений.
- У `/etc` читання деяких файлів було дозволено, запис практично завжди заборонений для звичайного користувача.

**Висновок:**  
Права доступу суворо контролюють можливість взаємодії з файлами системи.

---

## Завдання 16

У цьому завданні було виконано експеримент, що показує, що може трапитись, якщо внаслідок помилки в скрипті змінюються права доступу до критичного файлу системи, зокрема `/etc/shadow`.

### Опис експерименту:

1. **Нормальні права на `/etc/shadow`:**  
   У стандартних налаштуваннях Linux файл `/etc/shadow` має права доступу, які дозволяють лише адміністраторам (root) читати його, а також групі `shadow`, якщо така є. Це забезпечує безпеку зашифрованих паролів користувачів, оскільки цей файл містить чутливу інформацію.

   За замовчуванням права виглядають наступним чином:
   ```bash
   -rw-r----- 1 root shadow 1535 кві 29 10:00 /etc/shadow
   ```
   Це означає:
   - Власник (`root`) має право на читання і запис.
   - Група (`shadow`) має лише право на читання.
   - Інші користувачі не мають жодного доступу до цього файлу.

2. **Зміна прав доступу:**
   У межах цього експерименту була змінена команда, яка призвела до помилкового встановлення прав доступу:
   ```bash
   sudo chmod 644 /etc/shadow
   ```
   Після виконання цієї команди права на файл стали:
   ```bash
   -rw-r--r-- 1 root root 1535 кві 29 10:00 /etc/shadow
   ```
   Це означає:
   - Власник (`root`) має право на читання і запис.
   - Усі інші користувачі, включаючи тих, хто не має привілеїв адміністратора, можуть читати цей файл.
   
3. **Наслідки зміни прав:**
   - **Витік паролів:** Тепер будь-який користувач, навіть без прав адміністратора, може отримати доступ до файлу `/etc/shadow` і прочитати зашифровані паролі всіх користувачів. Хоча паролі зберігаються в зашифрованому вигляді, зловмисник може спробувати застосувати методи брутфорсу або таблиці радужних хешів для їх злому.
   - **Злом системи:** Наявність доступу до паролів може призвести до серйозного порушення безпеки. Ті, хто має змогу зчитувати вміст цього файлу, можуть отримати доступ до облікових записів, навіть якщо паролі зашифровані. Акти пошуку та злома паролів можуть бути автоматизовані.
   - **Попередження у системі безпеки:** Системи моніторингу безпеки, такі як `Lynis`, `Chkrootkit` або інші інструменти аудиту, зможуть виявити такі зміни у праві доступу і створять тривогу.

4. **Виправлення помилки:**
   Після виявлення цієї помилки було негайно відновлено правильні права доступу до файлу:
   ```bash
   sudo chmod 640 /etc/shadow
   sudo chown root:shadow /etc/shadow
   ```
   Тепер доступ до файлу знову обмежений тільки для користувача `root` і, якщо є, для групи `shadow`.

5. **Висновок:**
   Експеримент продемонстрував, як важливо правильно налаштовувати права доступу до критичних системних файлів, таких як `/etc/shadow`. Невірно налаштовані права можуть призвести до серйозних порушень безпеки, зокрема витоку паролів, а також підвищення ризику зломів. Це підкреслює важливість перевірки та обережності при змінах прав на важливі файли системи, особливо в автоматизованих скриптах, де може статися помилка.

---

# Висновок

У процесі виконання завдань була детально вивчена робота з обліковими записами, правами доступу до файлів і директорій у Linux-системах. Було підтверджено, що правильне управління правами та власністю файлів критично важливе для безпеки системи. Також стало очевидно, що навіть дрібна помилка в скриптах або конфігураціях може призвести до серйозних наслідків, таких як витік паролів або злом системи. Всі експерименти допомогли краще зрозуміти, як саме працюють механізми контролю доступу в Linux, і наскільки важливо підтримувати правильні права на критичні системні файли.
