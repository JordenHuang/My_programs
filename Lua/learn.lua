-- print('hi')


--[[
local function add_one(array, int)
    for i=0, #array, 1 do
        array[i] = array[i] + 1
    end
    
    int = int + 1
    return array, int  -- actually, don't need to return array
end


-- io.write("Enter n: ")
-- local n = io.read("n")


local array = {}

-- array[0] = "zero"

-- print(array[1])


for i=0, 5, 1 do
    array[i] = i
end


for i=0, 3, 1 do
    print(array[i])
end

local a = 10
print()
array, a = add_one(array, a)


for i=0, 3, 1 do
    print(array[i])
end
print()
print(a)



]]



--[[

-- table

local days = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"}
local rev_days = {}

for i, v in ipairs(days) do
    io.write(string.format("%d %s\n", i, v))
    rev_days[v]= i
end

print()

for i, v in ipairs(days) do
    io.write(string.format("%s %d\n", v, rev_days[v]))
end
-- print(rev_days["Sunday"])

]]



-- list

local function list_append(list_head, data)
    local new_node = {
        data = data,
        next = nil
    }
    if list_head == nil then
        list_head = new_node
    else
        local cur = list_head
        while cur.next ~= nil do
            cur = cur.next
        end
        cur.next = new_node
    end

    return list_head
end

local list_head = nil

for i=1, 10, 1 do
    list_head = list_append(list_head, i)
end

local cur = list_head

while cur do
    io.write(string.format("%d ", cur.data))
    cur = cur.next
end
