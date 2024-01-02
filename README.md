![image](https://github.com/Sasha300578/Alg_Tree_Iterator/assets/113348429/50caba1f-6907-4305-9b36-c899ef0b22f9)# Alg_Tree_Iterator
Программа, в которой реализован абстрактный тип данных "Дерево" для дерева двоичного поиска . Реализованы два обхода дерева: симметричный и обратный. Также написаны итераторы для данных обходов. Для деревьев реализована операция: А = A ⋂ B. Операция А = A ⋂ B означает, что из дерева А исключаются узлы, отсутствующие в дереве В. Реализация дерева: Указатель (курсор) на родителя

В программе есть 2 примера.
Пример 1
Дерево A до операции
![image](https://github.com/Sasha300578/Alg_Tree_Iterator/assets/113348429/5e9dab76-24c9-4f6f-9504-f1c9dc5dcce2)
Симметричный обход: 0,1,2,3,4,5,6,7,8,9

Дерево B до операции и его обход
![image](https://github.com/Sasha300578/Alg_Tree_Iterator/assets/113348429/7085d31a-e728-47e0-80bf-537ab82eb153)
Обратный обход: 0,1,4,3,2,11,7,5

Дерево A после операции и его обход
![image](https://github.com/Sasha300578/Alg_Tree_Iterator/assets/113348429/9080d34b-36cd-4114-a984-e970a0d67f2b)
Симметричный обход: 0,1,2,3,4,5,7

Вывод программы:
![image](https://github.com/Sasha300578/Alg_Tree_Iterator/assets/113348429/a6be69af-5f6a-4b3f-b703-fb0eab7aff56)

 
Пример 2
Дерево A до операции и его обход
![image](https://github.com/Sasha300578/Alg_Tree_Iterator/assets/113348429/cfaccc4e-f333-4aa9-b2a4-b48348adb781)
Симметричный обход: 1,2,3,4,7,8

Дерево B до операции и его обход
![image](https://github.com/Sasha300578/Alg_Tree_Iterator/assets/113348429/b3adb16b-22c2-4575-ac04-9c341404f291)
Обратный обход: 1,2,3

Дерево A после операции и его обход
![image](https://github.com/Sasha300578/Alg_Tree_Iterator/assets/113348429/d6dbccac-a019-476d-adef-a726a79c07bf)
Симметричный обход: 1,2,3

Вывод программы:
![image](https://github.com/Sasha300578/Alg_Tree_Iterator/assets/113348429/f3d7c43f-0346-4590-a66c-bcc4f25c6aad)

