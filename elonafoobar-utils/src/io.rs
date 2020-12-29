use std::io::{Read, Result, Seek, SeekFrom};

// Skip UTF-8 BOM if present.
pub fn skip_bom<R>(r: &mut R) -> Result<bool>
where
    R: Read + Seek,
{
    let mut buffer = [0; 3];
    let read_len = r.read(&mut buffer)?;
    if read_len == 3 && buffer == [0xEF, 0xBB, 0xBF] {
        Ok(true)
    } else {
        r.seek(SeekFrom::Start(0))?;
        Ok(false)
    }
}
