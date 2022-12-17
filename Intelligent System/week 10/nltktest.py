import nltk

# nltk.download('averaged_perceptron_tagger')
# nltk.download("punkt")

sentence = nltk.word_tokenize("I shot an elephant in my pajamas")
print(nltk.pos_tag(sentence))