import pandas as pd;

df1 = pd.DataFrame(pd.read_excel('test.xlsx'))
df2 = pd.DataFrame(pd.read_excel("group.xlsx"))

print(df2)

def match_group(x):
    for y in df2['key_word']:
        if str(y) in x:
            return y
    return '未收录'

df1['group'] = df1['add'].apply(match_group)
df1.to_excel('result.xlsx',index=None)