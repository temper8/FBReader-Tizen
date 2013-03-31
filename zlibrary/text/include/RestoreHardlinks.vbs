Dim fso1, ts, fileObj, TextLine, t3
Dim WshShell
set WshShell = WScript.CreateObject("WScript.Shell")

Set fso1 = WScript.CreateObject("Scripting.FileSystemObject")

Set oFolders = fso1.GetFolder(fso1.GetParentFolderName(WScript.ScriptFullName))

Set files = oFolders.Files

ext = "h"

For Each file In files
if fso1.getextensionname(file) = ext then  
	Set ts = file.OpenAsTextStream
	TextLine = ts.ReadLine
	ts.Close
        if Left(TextLine,3) ="../" then
	        strListFolders = strListFolders & file.Name& "-" & "-" &TextLine & vbCrLf
                fn=file.Name
'		fso1.DeleteFile(file.Name)
		WshShell.Run("%COMSPEC% /K fsutil hardlink create hardlink\"+fn+ " "+Textline)
		WScript.Sleep (200)
		end if
      end  if
Next   

MsgBox strListFolders