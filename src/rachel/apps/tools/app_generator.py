import os as os
from shutil import copytree
import re

app_name = ""
def getAppName():
    global app_name
    app_name = input("app name: ")
    app_name = app_name.lower()


def checkAppName():
    if app_name == "":
        return False
    if not re.match("^[a-zA-Z_]+$", app_name):
        return False
    if app_name == "template":
        return False
    return True
    

def creteApp():
    global app_name

    # Get file name
    folder_name = "../app_" + app_name
    source_file_name = folder_name + "/app_" + app_name + ".cpp"
    header_file_name = folder_name + "/app_" + app_name + ".h"
    print("file names:\n - {}\n - {}\n".format(source_file_name, header_file_name))

    # Create folder
    os.mkdir(folder_name)

    # Create files 
    source_file = open(source_file_name, mode='x')
    header_file = open(header_file_name, mode='x')

    # Read Template content
    content_source_file = open("../app_template/app_template.cpp", mode='r').read()
    content_header_file = open("../app_template/app_template.h", mode='r').read()

    # Replace app class
    app_class_name = app_name.capitalize()
    print("app class name: {}".format("App" + app_class_name))
    content_source_file = content_source_file.replace("Template", app_class_name)
    content_header_file = content_header_file.replace("Template", app_class_name)

    # Replace file name 
    content_source_file = content_source_file.replace("app_template", "app_" + app_name)
    content_header_file = content_header_file.replace("app_template", "app_" + app_name)

    # Write in
    source_file.write(content_source_file)
    header_file.write(content_header_file)

    # Close files
    source_file.close()
    header_file.close()

    # Copy asset folder 
    copytree("../app_template/assets", folder_name + "/assets")


def installApp():
    global app_name
    print("install app {}".format(app_name))

    # Read app install callback 
    app_install_cb_file = open("../apps.h", mode='r')
    content_app_install_cb_file = app_install_cb_file.read()
    app_install_cb_file.close()

    # Add including 
    header_include_tag = "/* Header files locator(Don't remove) */"
    content_app_install_cb_file = content_app_install_cb_file.replace(header_include_tag, "#include \"app_{}/app_{}.h\"\n{}".format(app_name, app_name, header_include_tag))

    # Add install mooncake->installApp(new MOONCAKE::APPS::AppTemplate_Packer);
    app_install_tag = "/* Install app locator(Don't remove) */"
    content_app_install_cb_file = content_app_install_cb_file.replace(app_install_tag, "mooncake->installApp(new MOONCAKE::APPS::App{}_Packer);\n    {}".format(app_name.capitalize(), app_install_tag))

    # Write app install callback 
    app_install_cb_file = open("../apps.h", mode='w+')
    app_install_cb_file.write(content_app_install_cb_file)
    app_install_cb_file.close()


if __name__=="__main__":
    print("Rachel app generator > <")
    
    while True:
        getAppName()
        if checkAppName():
            break
        else:
            print("bad name, try again")

    print("get app name: {}\n".format(app_name))
    
    creteApp()
    installApp()

    print("\ndone")
