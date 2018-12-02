# sentiment-analysis

Sentiment analysis is a technique that uses text processing for opinion mining, aiming to classify the opinion inside a text as neutral, positive or negative. This project implements the opinion mining in sentences using two different data structures to store the words and their values: an **AVL tree** and a **BST tree**. The method used may be choosen through preprocessors directives in tree.h. Usage:
     
```
./sentiment-analysis lexicon.txt senteces.txt output.txt
```
**lexicon.txt:** is a file with words and its values in the format *word\tvalue\n*  
**sencentes.txt:** the target sentences  
**output.txt:** the file where the output will be saved in the format *sentence_value sentence\n*  


