-- file: 'thanks.lua'
-- desc: to print the list of the contributing guys
function fact  (n)
	if n == 0 then
		return 1
	else
		return n*fact(n-1)
	end
end

print("please input a number")
a=io.read("*number")
print(fact(a))
