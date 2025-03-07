from PIL import Image
import os

folder_path = "C:/Users/paula/Desktop/super mario/gif"  # 修改成你的資料夾路徑
gif_files = os.listdir(folder_path)  # 獲取該資料夾中的所有檔案和資料夾名稱
for gif_file in gif_files:
    gif_path = os.path.join(folder_path, gif_file)
    
    # 以 GIF 檔名（去除副檔名）作為新資料夾名稱
    gif_name = os.path.splitext(gif_file)[0]
    gif_output_folder = os.path.join(folder_path, gif_name)

    # 建立子資料夾來存放該 GIF 的 PNG 幀
    os.makedirs(gif_output_folder, exist_ok=True)
    
    # 開啟 GIF 檔案
    with Image.open(gif_path) as img:
        frame_index = 0
        while True:
            frame_filename = f"frame{frame_index}.png"
            frame_path = os.path.join(gif_output_folder, frame_filename)

            # 儲存當前幀
            #img = img.convert("RGBA")
            img.save(frame_path, format="PNG")
            print(f"Saved: {frame_path}")

            frame_index += 1

            # 檢查是否還有下一幀
            try:
                img.seek(frame_index)
            except EOFError:
                break  # 讀取到最後一幀時停止