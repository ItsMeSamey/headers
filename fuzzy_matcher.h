#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>
#include <string.h>
#include <stddef.h>
#include <stdlib.h>

// Returns the Levenshtein distance between word1 and word2.
// Blatently ripped from - https://github.com/guilhermeagostinelli/levenshtein
int levenshtein_distance(const char *word1,const char *word2) {
  const size_t size1 = strlen(word1);
  const size_t size2 = strlen(word2);
  int verif[size1 + 1][size2 + 1], cost;

  // if (size1 == 0){return size2;}
  // if (size2 == 0){return size1;}
  for (size_t i = 0; i <= size1; i++){verif[i][0] = i;}
  for (size_t j = 0; j <= size2; j++){verif[0][j] = j;}

  for (size_t i = 1; i <= size1; i++) {
    for (size_t j = 1; j <= size2; j++) {
      cost = (verif[i-1][j] < verif[i][j-1]) ? verif[i-1][j] : verif[i][j-1];
      verif[i][j] = cost < verif[i-1][j-1]+((word2[j-1]==word1[i-1])?-1:0) ? cost+1 : verif[i-1][j-1]+((word2[j-1]==word1[i-1])?0:1);
    }
  }
  return verif[size1][size2];
}

void levenshtein_distance_sort(char *word, char **array_to_be_sorted, size_t size_of_array){
  int scores[size_of_array], temp_int;
  int max, max_index;
  char *temp_char;

  for (size_t i = 0; i < size_of_array; i++){
    scores[i] = levenshtein_distance(word, array_to_be_sorted[i]);
  }

  for (size_t i = size_of_array; i >0; i--){
    max = scores[0];
    max_index = 0;
    for (size_t j = 0; j < i; j++){
      if (max < scores[j]){
        max = scores[j];
        max_index = j;
      }
    }
    temp_char = array_to_be_sorted[i-1];
    array_to_be_sorted[i-1] = array_to_be_sorted[max_index];
    array_to_be_sorted[max_index] = temp_char;
    scores[max_index] = scores[i-1];
    scores[i-1] = max;
  }
}

char **levenshtein_distance_sort(char *word, char *string_of_words, size_t optional_word_count = 0, size_t optional_strlen = 0){
  char *end_of_string = optional_strlen+string_of_words;

  if (optional_word_count == 0){
    if (optional_strlen == 0){printf("ERR in levenshtein_distance_sort,\n size_of_string == 0 and optional_word_count == 0 ");return NULL;}
    for (char *i = string_of_words; i < end_of_string;i++){if (*i == '\0'){optional_word_count++;}}
    if (*(end_of_string-1) != '\0' && *end_of_string == '\0'){optional_word_count++;}// if you missed the end by one
  }

  char **array_to_be_sorted = (char **)malloc(optional_word_count * sizeof(char*));
  array_to_be_sorted[0] = string_of_words;
  size_t index = 1;

  for (char *i = string_of_words;index < optional_word_count;i++){if (*i == '\0'){array_to_be_sorted[index++] = i+1;}}
  levenshtein_distance_sort(word, array_to_be_sorted, optional_word_count);
  return array_to_be_sorted;
}

#ifdef __cplusplus
};
#endif

