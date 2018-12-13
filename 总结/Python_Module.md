## Python module ##

### tqdm ###
Module Name : ```tqdm```  
Type : ```third part```  
Sample :  
```python
    text = ""
    for char in tqdm(["a", "b", "c", "d"]): #can be any list, like range(20,1000)
        text = text + char
        time.sleep(0.5)
```
```python
    with tqdm(total=100) as pbar:
        for i in range(10):
            pbar.update(10)
```  
Doc : https://github.com/tqdm/tqdm#documentation  
