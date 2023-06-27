use std::{env, fs}; // add imports
use std::path::Path;
use std::io::Write;
use std::io;
use std::path::PathBuf; //add import

use crate::row::Row;

pub struct EditorRows {
     row_contents: Vec<Row>, // modify
	 pub filename: Option<PathBuf>, //add field
}

impl EditorRows {
	
	 /* modify function*/
    pub fn new() -> Self {
        let mut arg = env::args();

        match arg.nth(1) {
            None => Self {
                row_contents: Vec::new(),
				 filename: None, // add line
            },
            Some(file) => Self::from_file(file.as_ref()),
        }
    }

    fn from_file(file: &Path) -> Self {
        let file_contents = fs::read_to_string(file).expect("Unable to read file");
        /* modify */
        Self {
			filename: Some(file.to_path_buf()), //add line
            row_contents: file_contents
                .lines()
                .map(|it| {
                    let mut row = Row::new(it.into(), String::new());
                    Self::render_row(&mut row);
                    row
                })
                .collect(),
        }
       /* end */
    }
	pub fn render_row(row: &mut Row) {
        let mut index = 0;
        let capacity = row
            .row_content
            .chars()
            .fold(0, |acc, next| acc + if next == '\t' { 8 } else { 1 });
        row.render = String::with_capacity(capacity);
        row.row_content.chars().for_each(|c| {
            index += 1;
            if c == '\t' {
                row.render.push(' ');
                while index % 8 != 0 {
                    row.render.push(' ');
                    index += 1
                }
            } else {
                row.render.push(c);
            }
        });
    }
    pub fn number_of_rows(&self) -> usize {
        self.row_contents.len() /* modify */
    }

	    /* add functions*/
    pub fn get_render(&self, at: usize) -> &String {
        &self.row_contents[at].render
    }
    
    
    pub fn get_editor_row(&self, at: usize) -> &Row {
        &self.row_contents[at]
    }
	
	pub fn insert_row(&mut self, at: usize, contents: String) {
        let mut new_row = Row::new(contents, String::new());
        EditorRows::render_row(&mut new_row);
        self.row_contents.insert(at, new_row);
    }
	
	    //add function
    pub fn get_editor_row_mut(&mut self, at: usize) -> &mut Row {
        &mut self.row_contents[at]
    }
	pub fn join_adjacent_rows(&mut self, at: usize) {
        let current_row = self.row_contents.remove(at);
        let previous_row = self.get_editor_row_mut(at - 1);
        previous_row.row_content.push_str(&current_row.row_content);
        Self::render_row(previous_row);
    }
	
    pub fn save(&self) -> io::Result<()> {
        match &self.filename {
            //None => Err(io::Error::new(ErrorKind, "no file name specified")),
			None => Err(io::ErrorKind::WriteZero.into()),
            Some(name) => {
                let mut file = fs::OpenOptions::new().write(true).create(true).open(name)?;
                let contents: String = self
                    .row_contents
                    .iter()
                    .map(|it| it.row_content.as_str())
                    .collect::<Vec<&str>>()
                    .join("\n");
                file.set_len(contents.len() as u64)?;
                file.write_all(contents.as_bytes())
                
            }
        }
    }
}