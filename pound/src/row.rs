use crate::EditorRows;

#[derive(Default)] //add line
pub struct Row {
    pub row_content: String, // modify
    pub render: String,
}

impl Row {
    pub fn new(row_content: String, render: String) -> Self { //modify
        Self {
            row_content,
            render,
        }
    }
	    /* add function*/
    pub fn insert_char(&mut self, at: usize, ch: char) {
        self.row_content.insert(at, ch);
        EditorRows::render_row(self)
    }
	    /* add function */
    pub fn delete_char(&mut self, at: usize) {
        self.row_content.remove(at);
        EditorRows::render_row(self)
    }
}



