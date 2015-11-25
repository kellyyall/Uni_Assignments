# SWEN30006 Software Modelling and Design, 2014, sem2, project1
# The algorithm is according to the content on this website:
# http://practicalcryptography.com/cryptanalysis/text-characterisation/chi-squared-statistic/
# Implemented by Kelly Yang (566123)

# This caesar_cipher function is refered to
# https://github.com/ooofinooo/caesar_cipher/blob/master/caesar_cipher.rb
def caesar_cipher(string, shift)
  lowercase_alphabet = 'a'.upto('z').to_a
  uppercase_alphabet = 'A'.upto('Z').to_a
  encrypted = []

  string.split('').each do |x|
    if lowercase_alphabet.include?(x)
      shift -= 26 if lowercase_alphabet.index(x) + shift >= 25
      encrypted << lowercase_alphabet[lowercase_alphabet.index(x)+shift]
    elsif uppercase_alphabet.include?(x)
      shift -= 26 if uppercase_alphabet.index(x) + shift >= 25
      encrypted << uppercase_alphabet[uppercase_alphabet.index(x)+shift]
    else
      encrypted << x
    end
  end
  encrypted.join
end

puts "Your Ciphertext: "
STDOUT.flush  
str = gets
str_lowercase=str.downcase
text_string = str_lowercase.scan(/\w/).inject(Hash.new(0)){|h, c| h[c] += 1; h}

# Calculate the total number of char in the text (the whole string)
total_char = 0
text_string.each do |key, value|
  total_char = total_char + value
end

# Set the chi_squared statistic to 0, I need to find the smallest statistic.
mini_chi_value = 0

 $shift = 0
 $final = 26
while $shift < $final do      # shift the text 25 times + the start text 
shift_text= caesar_cipher(str_lowercase,$shift)
text_res = shift_text.scan(/\w/).inject(Hash.new(0)){|h, c| h[c] += 1; h}
$shift +=1

# Frequency of letters in English text
fre_english={"a"=> 0.0817, "b"=>0.0149, "c"=>0.0278, "d"=>0.0425,
              "e"=>0.1270, "f"=>0.0223, "g"=>0.0202, "h"=>0.0609,
              "i"=>0.0697, "j"=>0.0015, "k"=>0.0077, "l"=>0.0403,
              "m"=>0.0241, "n"=>0.0675, "o"=>0.0751, "p"=>0.0193,
              "q"=>0.0009, "r"=>0.0599, "s"=>0.0633, "t"=>0.0905,
              "u"=>0.0276, "v"=>0.0098, "w"=>0.0236, "x"=>0.0015,
              "y"=>0.0197, "z"=>0.0007}

# Calculate the chi_squared statistic for each shifted text.
chi_squared_value=0;

fre_english.each do |fre_key, fre_value|
   text_res.each do |text_key,text_value|
     if text_key == fre_key
      normal_fre = fre_value*total_char
      chi_char_value = ((text_value - normal_fre)**2)/normal_fre
      chi_squared_value = chi_squared_value + chi_char_value
      fre_english.delete(fre_key)
     end
   end
end

fre_english.each do |no_key, no_value|
    chi_squared_value = chi_squared_value + no_value*total_char
  end

current_chi = chi_squared_value

# Find the smallest chi_squared statistic and record the shift value.
if mini_chi_value ==0
  mini_chi_value = chi_squared_value
  elsif 
    current_chi<mini_chi_value
    mini_chi_value = current_chi
    final_shift = $shift - 1
  end
end 
  
puts "Plaintext: "
puts caesar_cipher(str,final_shift)

puts "The key is:"
puts final_shift
