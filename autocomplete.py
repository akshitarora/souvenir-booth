#!/usr/bin/env python
import sys

class Node:
	def __init__(self):
		self.next = {}	#Initialize an empty hash (python dictionary)
		self.word_marker = False 
		# There can be words, Hot and Hottest. When search is performed, usually state transition upto leaf node is peformed and characters are printed. 
		# Then in this case, only Hottest will be printed. Hot is intermediate state. Inorder to mark t as a state where word is to be print, a word_marker is used


	def add_item(self, string): 
		''' Method to add a string the Trie data structure'''
		
		if len(string) == 0:
			self.word_marker = True 
			return 
		
		key = string[0] #Extract first character
		string = string[1:] #Create a string by removing first character

		# If the key character exists in the hash, call next pointing node's add_item() with remaining string as argument
		if self.next.has_key(key):
			self.next[key].add_item(string)
		# Else create an empty node. Insert the key character to hash and point it to newly created node. Call add_item() in new node with remaining string.
		else:
			node = Node()
			self.next[key] = node
			node.add_item(string)


	def dfs(self, sofar=None): 
		'''Perform Depth First Search Traversal'''
		
		# When hash of the current node is empty, that means it is a leaf node. 
		# Hence print sofar (sofar is a string containing the path as character sequences through which state transition occured)
		if self.next.keys() == []:
			print "Match:",sofar
			return
			
		if self.word_marker == True:
			print "Match:"+sofar

		# Recursively call dfs for all the nodes pointed by keys in the hash
		for key in self.next.keys():
			self.next[key].dfs(sofar+key)

	def search(self, string, sofar=""): 
		'''Perform auto completion search and print the autocomplete results'''
		# Make state transition based on the input characters. 
		# When the input characters becomes exhaused, perform dfs() so that the trie gets traversed upto leaves and print the state characters
		if len(string) > 0:
			key = string[0]
			string = string[1:]
			if self.next.has_key(key):
				sofar = sofar + key
				self.next[key].search(string,sofar)
				
			else:
				print "No match"
		else:
			if self.word_marker == True:
				print "Match:",sofar

			for key in self.next.keys():
				self.next[key].dfs(sofar+key)


def fileparse(filename):
	'''Parse the input dictionary file and build the trie data structure'''
	fd = open(filename)

	root = Node()	
	line = fd.readline().strip('\r\n') # Remove newline characters \r\n

	while line !='':
		root.add_item(line)
		line = fd.readline().strip('\r\n')

	return root



if __name__ == '__main__':

	
		
	root  = fileparse("dictionary.txt")

	print "Input:",
	input=raw_input()
	root.search(input)



