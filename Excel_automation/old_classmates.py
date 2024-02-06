import openpyxl

wb = openpyxl.load_workbook('file2.xlsx')

ws = wb.active

names = ws['B']

for name in names:
    if name.row == 1: continue
    print(name.value)
